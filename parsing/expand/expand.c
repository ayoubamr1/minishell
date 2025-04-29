/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 18:13:43 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
 
char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (res);
}

static int	ft_numlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char *remove_quotes(const char *str)
{
	int i;
	int j;
	char quote;
	char *res;

	(1) && (i = 0, j = 0, quote = 0);
	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

static char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static char	*expand_pid(char *res)
{
	pid_t	pid;
	char	*pid_str;
	char	*tmp;

	pid = getpid();
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (res);
	tmp = join_and_free(res, pid_str);
	return (tmp);
}

static char *cher_env(char *key, t_env *env)
{
    t_env *tmp;
    char *search;
    size_t key_len;

    tmp = env;
    search = ft_strjoin(key, "=");
    key_len = strlen(key);

    while (tmp)
    {
        if (!strncmp(search, tmp->content, key_len + 1))
        {
            free(search);
            return (ft_strdup(tmp->content + key_len + 1));
        }
        tmp = tmp->next;
    }
    free(search);
    return (ft_strdup(""));
}

static char	*expand_env_var(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;

	start = ++(*i);
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	key = substr(str, start, *i - start);
	val = cher_env(key, env);
	free(key);
	tmp = join_and_free(res, val);
	return (tmp);
}

static char	*ft_expand_token(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			res = expand_pid(res);
			i += 2;
		}
		else if (str[i] == '$' && str[i + 1] && ft_isalpha(str[i + 1]))
			res = expand_env_var(str, &i, env, res);
		else
		{
			tmp = substr(str, i, 1);
			res = join_and_free(res, tmp);
			i++;
		}
	}
	return (res);
}

void ft_expand(t_shell *shell)
{
    t_token *tok = shell->token;

    while (tok)
    {
        if (tok->type == WORD)
        {
            char *expanded = ft_expand_token(tok->content, shell->env);
            free(tok->content);
			tok->content = remove_quotes(expanded);
        }
		else if (tok->type == SI_QUOTE)
			tok->content = remove_quotes(tok->content);
        tok = tok->next;
    }
}

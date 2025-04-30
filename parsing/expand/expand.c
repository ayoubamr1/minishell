/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 18:47:50 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_pid(char *res)
{
	pid_t	pid;
	char	*pid_str;
	char	*tmp;

	pid = getpid();
	pid_str = id_itoa(pid);
	if (!pid_str)
		return (res);
	tmp = ft_strjoin(res, pid_str);
	return (tmp);
}

static char	*cher_env(char *key, t_env *env)
{
	t_env	*tmp;
	char	*search;
	size_t	key_len;

	tmp = env;
	search = ft_strjoin(key, ft_strdup("="));
	key_len = strlen(key);
	while (tmp)
	{
		if (!strncmp(search, tmp->content, key_len + 1))
		{
			// free(search);
			return (ft_strdup(tmp->content + key_len + 1));
		}
		tmp = tmp->next;
	}
	// free(search);
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
	// free(key);
	tmp = ft_strjoin(res, val);
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
			res = ft_strjoin(res, tmp);
			i++;
		}
	}
	return (res);
}

void	ft_expand(t_shell *shell)
{
	t_token	*tok;
	char	*expanded;

	tok = shell->token;
	while (tok)
	{
		if (tok->type == WORD)
		{
			expanded = ft_expand_token(tok->content, shell->env);
			// free(tok->content);
			tok->content = remove_quotes(expanded);
		}
		else if (tok->type == SI_QUOTE)
			tok->content = remove_quotes(tok->content);
		tok = tok->next;
	}
}

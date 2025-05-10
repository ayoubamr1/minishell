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
	// search = ft_strjoin(key, ft_strdup("="));
	key_len = strlen(key);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, key, key_len))
		{
			return (ft_strdup(tmp->content + key_len));
		}		
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
// static char	*cher_env(char *key, t_env *env)
// {
// 	t_env	*tmp;
// 	char	*search;
// 	size_t	key_len;

// 	search = ft_strjoin(key, "=");
// 	// if (!search)
// 	// 	return (ft_strdup("")); // or handle NULL case

// // printf("??%s\n", search);
// 	key_len = strlen(search);
// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("++++++++++++++++++\n");
// 		printf("Checking: [%s] against [%s]\n", tmp->content, search);
// 		printf("++++++++++++++++++\n");
// 		if (!strncmp(tmp->content, search, key_len))
// 		{
// 			// free(search);
// 			return (ft_strdup(tmp->content + key_len));
// 		}
// 		tmp = tmp->next;
// 	}
// 	// free(search);
// 	return (ft_strdup(""));
// }


static int	is_special_charr(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'' || c == ' ' || c == '$');
}

static char	*expand_env_var(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;
	char 	*env_path;
	int		j;

	start = ++(*i);
	j = 0;
	while (str[*i] && ft_isalpha(str[*i]) && !is_special_charr(str[*i]))
		(*i)++;
	key = substr(str, start, *i - start);
	printf("key =>[%s]\n", key);
	val = cher_env(key, env);
	if (!val)
		return(NULL);
	env_path = ft_malloc(sizeof(val), MALLOC); 
	while (val[j] && val[j] != '=')
		j++;
	j++;
	int p = 0;

	while (val[j])
	{
		env_path[p++] = val[j++];

	}
	env_path[p] = '\0';
	tmp = ft_strjoin(res, env_path);
	return (tmp);
}

static char *ft_dolar(char *str)
{
	int i;
	int p;
	char *new;

	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
		{
			new[p++] = str[i++];
		}
	}
	new[p] = '\0';
	// printf("nw => [%s]\n", new);
	return(new);
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

	// printf("str =>[%s]\n", str);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			res = expand_pid(res);
			i += 2;
		}
		else if (str[i] && (str[i] == '$') && str[i + 1] && ft_isalpha(str[i + 1]))
			res = expand_env_var(str, &i, env, res);
		else
		{
			tmp = substr(str, i, 1);
			res = ft_strjoin(res, tmp);
			i++;
		}
	}
	// printf("res =>[%s]\n", res);
	return (ft_dolar(res));
}
static char	*ft_expand_singl(char *str, t_env *env)
{
	int i;
	char quote;
	char *res;

	res = ft_strdup("");
	char	*tmp;
	quote = 0;
	i = 0;
	int start = 0;
	printf(">>%s\n", str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			start = i;
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			// if (str[i] == quote)
			res = substr(str, start, i - start);
				i++;
		}
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			res = expand_pid(res);
			i += 2;
		}
		else if (str[i] && (str[i] == '$') && str[i + 1] && ft_isalpha(str[i + 1]))
		{
			printf("c=> [%c]\n", str[i + 1]);
			res = expand_env_var(str, &i, env, res);
		}
		else
		{
			tmp = substr(str, i, 1);
			res = ft_strjoin(res, tmp);
			i++;
		}

	}
		printf(">>[%s]\n", res);
	return (ft_dolar(res));
	
}
void	ft_expand(t_shell *shell)
{
	t_token	*tok;
	char	*expanded;
	char	*dol;

	tok = shell->token;
	while (tok)
	{
		if (tok->type == WORD)
		{
			expanded = ft_expand_token(tok->content, shell->env);
			// printf(">>>>[%s]\n", expanded);
			tok->content = remove_quotes(expanded);
		}
		else if (tok->type == SI_QUOTE)
		{
			dol = ft_expand_singl(tok->content, shell->env);
			tok->content = remove_quotes(dol);
		}
		tok = tok->next;
	}
}

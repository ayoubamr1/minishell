/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/06 10:12:15 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char	*expand_pid(char *res, char *str, int i)
// {
// 	pid_t	pid;
// 	char	*pid_str;
// 	char	*tmp;
// 	int		start;

// 	start = i;
// 	// i = i + 2;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
// 			i++;
// 			// printf(">>[%s]\n", substr(str, start, i - start));
// 			// printf(">>[%s]\n",res);
// 			// printf(">>[%s]\n",ft_strjoin(res, substr(str, start, i - start)));
// 			return(ft_strjoin(res, substr(str, start, i - start)));
// 		}
// 		i++;
// 	}
// 	pid = getpid();
// 	// printf("PID = %ld\n", pid);
// 	pid_str = id_itoa(pid);
// 	if (!pid_str)
// 		return (res);
// 	tmp = ft_strjoin(res, pid_str);
// 	return (tmp);
// }

char *cher_env(char *key, t_env *env)
{
	t_env	*tmp;
	size_t	name_len;
	char	*equal;

	tmp = env;
	if (!key || !env)
		return (ft_strdup(""));
	while (tmp)
	{
		equal = ft_strchr(tmp->content, '=');
		if (equal)
		{
			name_len = equal - tmp->content;
			if (ft_strlen(key) == name_len && ft_strncmp(tmp->content, key, name_len) == 0)
				return (ft_strdup(equal + 1));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	is_special_char2(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '$');
}

char	*expand_env_var(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;
	char	quot;

	quot = 0;
	start = 0;
	while (str[start] && start < (*i))
	{
		if ((str[start] == '\'' || str[start] == '"') && quot == 0)
			quot = str[start];
		else if (str[start] == quot)
			quot = 0;
		start++;
	}
	start = ++(*i);
	while (str[*i] && ft_isalpha(str[*i]) && !is_special_char2(str[*i]))
		(*i)++;
	key = substr(str, start, *i - start);
	val = cher_env(key, env);
	if (!val)
		return(res);
	if (quot == '\'')
		return(ft_strjoin(res, ft_strjoin("$", key)));
	return (ft_strjoin(res, val));
}

char *ft_dolar(char *str)
{
	int i;
	int p;
	char *new;
	char qout;

	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] &&  str[i] == '"' || str[i] == '\'')
		{
			(1) && (new[p++] = str[i], qout = str[i++]);
			while (str[i] && str[i] != qout)
				new[p++] = str[i++];
			if (str[i] == qout)
				new[p++] = str[i++];
			new[p] = '\0';	
		}
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
			new[p++] = str[i++];
	}
	return(new[p] = '\0', new);
}

int ft_quote(char c)
{
	return (c == '"' || c == '\'');
}
char *strjoin_char(char *str, char c)
{
    size_t len;

	len = 0;
    if (str)
        len = ft_strlen(str);
    char *new_str = ft_malloc(len + 2, MALLOC);
    if (str)
        memcpy(new_str, str, len);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return (new_str);
}

char	*handle_ansi_c_quote(char *str, int *i, char *res)
{
	res = strjoin_char(res, str[*i]); // Add $
	(*i)++;
	res = strjoin_char(res, str[*i]); // Add '
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*handle_regular_quotes(char *str, int *i, char *res, char *quot)
{
	if ((str[*i] == '\'' || str[*i] == '"') && *quot == 0)
	{
		*quot = str[*i];
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	else if (str[*i] == *quot)
	{
		*quot = 0;
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

int ft_check_sp(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return(1);
		i++;
	}
	return(0);
}

char *remove_multi_space(char *str)
{
	char	*new;
	int		i;
	int		p;

	if (!str)
	return(str);
	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	p = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ' || str[i] == ' ' && str[i + 1] == '\0')
			i++;
		else
			new[p++] = str[i++];
	}
	new[p] = '\0';
	return (new);
}

char	*handle_variable_expansion(char *str, int *i, t_env *env, char *res)
{
	if (str[*i] == '$' && str[*i + 1] == '$')
	{
		// res = expand_pid(res, str, *i);
		*i += 2;
	}
	else if (str[*i] == '$' && str[*i + 1] && ft_isalpha(str[*i + 1]) 
	&& !ft_quote(str[*i + 1]))
	{
		if (!ft_check_sp(str))
			res = remove_multi_space(expand_env_var(str, i, env, res));
		else
			res = expand_env_var(str, i, env, res);
	}
	else if (str[*i] == '$' && str[*i + 1] && !ft_isalpha(str[*i + 1]) 
		&& !ft_quote(str[*i + 1]))
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	else
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*ft_expand_token(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	quot;

	i = 0;
	quot = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\'')
			res = handle_ansi_c_quote(str, &i, res);
		else
		{
			res = handle_regular_quotes(str, &i, res, &quot);
			if (str[i])
				res = handle_variable_expansion(str, &i, env, res);
		}
	}
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
		if (tok->type == WORD || tok->type == SI_QUOTE)
		{
			expanded = ft_expand_token(tok->content, shell->env);
			tok->content = remove_quotes(expanded);
		}
		else if (tok->type == DILIMITER)
			tok->content = remove_quotes(tok->content);
		tok = tok->next;
	}
}

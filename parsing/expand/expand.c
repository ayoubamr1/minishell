/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/07 17:39:07 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (ft_check_sp(str))
			env->flag = 1;
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

char **ft_join2d(char **s1, char **s2)
{
	int		i;
	int		p;
	int		len;
	char	**new;

	if ((!s1 || !s1[0]) && s2)
		return s2;
	if ((!s2 || !s2[0]) && s1)
		return s1;
	i = 0;
	p = 0;
	len = ft_count_2d(s1) + ft_count_2d(s2);
	new = ft_malloc(sizeof(char *) * (len +1), MALLOC);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[p])
		new[i++] = s2[p++];
	new[i] = NULL;
	return (new);
}

t_token	*split_token_ex(t_token *tok, char *str, t_shell *shell)
{
	char	**spl = ft_split(str, ' ');
	t_token	*first_new = NULL;
	t_token	*last = NULL;
	t_token	*save;
	int		i;
	
	shell->env->flag = 0;
	if (!spl || !spl[0])
		return (tok);
	save = tok->next;
	tok->content = spl[0];
	i = 1;
	last = tok;
	while (spl[i])
	{
		tok->next = new_token(spl[i++], WORD);
		tok = tok->next;
	}
	tok->next = save;
	return last;
}

void	ft_expand(t_shell *shell)
{
	t_token	*tok = shell->token;
	char	*expanded;

	while (tok)
	{
		if ((tok->type == WORD || tok->type == SI_QUOTE) && ft_strchr(tok->content, '$'))
		{
			expanded = remove_quotes(ft_expand_token(tok->content, shell->env));
			
			if (!expanded || !expanded[0])
				tok->content = ft_strdup("");
			else if (shell->env->flag == 1 || !ft_strchr(expanded, ' '))
			{
				tok->content = expanded;
				
			}
			else
				tok = split_token_ex(tok, expanded, shell);
		}
		else if (tok->type == WORD || tok->type == SI_QUOTE)
			tok->content = remove_quotes(tok->content);

			tok = tok->next;
	}	
}

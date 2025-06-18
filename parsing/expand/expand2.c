/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:17:29 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/18 15:55:29 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*cher_env(char *key, t_env *env, char	quot)
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
			if (ft_strlen(key) == name_len
				&& ft_strncmp(tmp->content, key, name_len) == 0)
				return (ft_strdup(equal + 1));
		}
		tmp = tmp->next;
	}
	if (quot == 0)
		env->quot = 1;
	return (ft_strdup(""));
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
	val = cher_env(key, env, quot);
	if (!val)
		return (res);
	if (quot == '\'')
		return (ft_strjoin(res, ft_strjoin("$", key)));
	return (ft_strjoin(res, val));
}

char	*ft_dolar(char *str)
{
	int		i;
	int		p;
	char	*new;
	char	qout;

	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
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
	return (new[p] = '\0', new);
}

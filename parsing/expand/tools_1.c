/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:13:18 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/07 18:16:02 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_special_char2(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '$');
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

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;
	
	if (!str)
		return (NULL);
	(1) && (i = 0, j = 0);
	quote = 0;
	res = ft_malloc(strlen(str) + 1, MALLOC);
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '"')
			res[j++] = str[i++];
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else
			return (res[j] = '\0', res);
		while (str[i] && str[i] != quote)
			res[j++] = str[i++];
		if (str[i])
			i++;
		while (str[i] && !is_special_char(str[i]))
			res[j++] = str[i++];
	}
	return (res[j] = '\0', res);
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

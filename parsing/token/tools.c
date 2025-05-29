/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/05/29 12:04:27 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*tok;

	tok = ft_malloc(sizeof(t_token), MALLOC);

	tok->content = content;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **lst, char *content, t_token_type type, int index)
{
	t_token	*tok;
	t_token	*tmp;

	tok = new_token(content, type);
	tok->index = index;
	if (!*lst)
		*lst = tok;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tok;
	}
}

char	*substr(char *s, int start, int len)
{
	char	*out;

	out = ft_malloc((len + 1), MALLOC);
	ft_strncpy(out, s + start, len);
	out[len] = 0;
	return (out);
}

int ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
    	return 1;
	return 0;
}

static size_t	ft_count_2d(char **arr)
{
	size_t	i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_strjoin2d(char **s1, char *s2)
{
	size_t	len1;
	size_t	i;
	char	**new;

	len1 = ft_count_2d(s1);
	i = 0;
	if (!s1 && s2)
		return (new = ft_malloc(2 * sizeof(char *), MALLOC), new[0] = ft_strdup(s2), new[1] = NULL, new); 
	if (s1 && !s2)
		return (s1);
	new = ft_malloc(sizeof(char *) * (len1 + 2), MALLOC);
	while (i < len1)
	{
		new[i] = ft_strdup(s1[i]);
		i++;
	}
	new[i++] = ft_strdup(s2);
	new[i] = NULL;
	return (new);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

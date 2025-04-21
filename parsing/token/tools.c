/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/21 15:24:35 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*tok;

	tok = ft_malloc(sizeof(t_token), MALLOC);
	if (!tok)
		return (NULL);
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
	if (!out)
		return (NULL);
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

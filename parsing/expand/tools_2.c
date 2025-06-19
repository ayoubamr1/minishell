/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:03:54 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/19 21:31:57 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*split_token_ex(t_token *tok, char *str, t_shell *shell)
{
	char	**spl;
	t_token	*last;
	t_token	*save;
	int		i;

	spl = ft_split(str, ' ');
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
	return (last);
}

char	**ft_split_space(char *str)
{
	char	**new;
	char	quote;
	int		start;
	int		i;

	(1) && (quote = 0, new = NULL, i = 0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		start = i;
		while (str[i] && str[i] != ' ')
		{
			if (ft_quote(str[i]))
			{
				quote = str[i++];
				while (str[i] && str[i] != quote)
					i++;
			}
			i++;
		}
		new = ft_strjoin2d(new, remove_quotes(substr(str, start, i - start)));
	}
	return (new);
}

t_token	*split_to_token_list(t_token *tok, char **spl)
{
	t_token	*last;
	t_token	*save;
	int		i;

	if (!spl || !(*spl))
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
	return (tok);
}

char	*up_token(char *str, int i)
{
	char	*new;
	int		start;
	int		j;

	new = ft_malloc(ft_strlen(str + i) + 3, MALLOC);
	start = i;
	j = 0;
	new[j++] = '"';
	while (str[i])
		new[j++] = str[i++];
	new[j++] = '"';
	new[j++] = '\0';
	new = ft_strjoin(substr(str, 0, i - start), new);
	return (new);
}

t_token	*token_up(t_token *token)
{
	t_token	*tmp;
	int		i;
	int		start;

	tmp = token;
	while (tmp && tmp->next)
	{
		if (tmp->type == WORD && tmp->next->type == WORD)
		{
			if (!ft_strcmp(tmp->content, "export"))
			{
				tmp = tmp->next;
				i = 0;
				while (tmp->content[i] && tmp->content[i] != '=')
					i++;
				if (tmp->content[i] && tmp->content[i + 1])
					i++;
				if (tmp->content[i] && (!ft_strchr(tmp->content + i, '"')
						&& ft_strchr(tmp->content + i, '$')))
					tmp->content = up_token(tmp->content, i);
			}
		}
		tmp = tmp->next;
	}
	return (token);
}

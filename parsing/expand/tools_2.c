/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:03:54 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/18 18:52:22 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_sp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

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

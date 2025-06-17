/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:03:54 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/14 15:45:57 by nbougrin         ###   ########.fr       */
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
	return (last);
}

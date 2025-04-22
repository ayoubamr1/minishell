/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/22 19:12:45 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_commend(t_token **token, t_token **commend_list)
{
	t_token *tmp;
	int		p;

	tmp = *token;
	p = 1;
	while (tmp)
	{
		if (tmp->type == PIPE)
			p++;
		tmp = tmp->next;
	}
	tmp = *token;
		printf("***********\n");
	if (tmp && tmp->next && (tmp->next->content[0] == '-'))
	{
		add_token(commend_list, ft_strjoin(ft_strjoin(tmp->content, " "), tmp->next->content), VOID, 0);
		tmp = tmp->next->next;
		printf("{%s}\n", (*commend_list)->content);
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			// if ()
				add_token(commend_list, ft_strjoin(ft_strjoin(tmp->content, " "), tmp->next->content), VOID, 0);
		}
		else if ((tmp->type == REDIR_IN) || (tmp->type == REDIR_OUT))
		{
			
		} 
			tmp = tmp->next;
	}
}
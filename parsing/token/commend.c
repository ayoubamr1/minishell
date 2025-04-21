/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/21 20:17:12 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_commend(t_token **token, t_token **commend_list)
{
	t_token *tmp;

	tmp = *token;
	if (tmp->next->content[0] == '-')
	{
		add_token(commend_list, ft_strjoin(ft_strjoin(tmp->content, " "), tmp->next->content), VOID, 0);
		tmp = tmp->next->next;
	}
	while (tmp)
	{
		tmp = tmp->next;
	}
	






}
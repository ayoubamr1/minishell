/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:20:33 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/04 18:05:45 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_exite(t_shell *main)
{
	t_cmd *curr;
	
	curr = main->cmd;
	if (!strncmp(curr->cmd[0], "exit", ft_strlen("exit")))
	{
		ft_malloc(0, FREE);
		exit(0);
		exite_status = 0;
	}
	else
		exite_status = 1;
}
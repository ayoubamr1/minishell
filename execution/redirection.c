/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:02:19 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/22 16:32:42 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redir(t_shell *main)
{
	t_cmd *curr;

	curr = main->cmd;
	while (curr)
	{
		// printf("cmd[0] = %s\n", curr->cmd[0]);
		// printf("cmd[0] = %p\n", curr->cmd[0]);
		if (!curr->cmd && curr->next && curr->next->cmd)
		{
			pipe(curr->pipe_fd);
			close(curr->pipe_fd[1]);
			curr->next->in = curr->pipe_fd[0];
			// printf("next in_fd = %d\n", curr->next->in);
		}
		curr = curr->next;
	}
}

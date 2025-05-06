/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:02 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/06 15:55:21 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commande(t_cmd *cmd, t_env **env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	pid_t	pid;
	
	cur = cmd;
	while (cur)
	{
		if (cur->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe filled\n");
				exit(EXIT_FAILURE);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			if (pid == 0) // child process
			{
				if (cur->in != 0)
					dup2(cur->in, 0);
					
			}
		}
	}
	
}
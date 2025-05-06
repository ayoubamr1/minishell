/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:02 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/06 17:13:50 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commande(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_read;
	
	cur = cmd;
	prev_read = 0;
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
				else if (prev_read)
					dup2(prev_read, 0);
				if (cur->out != 1)
					dup2(cur->out, 1);
				else if (cur->next)
					dup2(pipe_fd[1], 1);
				if (execve(cur->cmd[0], cur->cmd, env->content) == -1)
				{
					perror("exec failled\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		cur = cur->next;
	}
}
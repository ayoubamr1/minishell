/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:26 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/09 18:15:12 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commande(t_shell *main)
{
	t_cmd	*cur;
	char	**path;
	
	cur = main->cmd;
	cur->prev_read = 0;
	// cur->pid = malloc((cur->cmd) * sizeof(pid_t));
	while (cur)
	{
		if (cur->next)
		{
			ft_creat_pipe(cur);
			ft_fork_process(cur);
			if (cur->pid == 0) // child process
			{
				// close(cur->pipe_fd[0]);
				if (cur->in != 0)
					dup2(cur->in, 0);
				else if (cur->prev_read)
					dup2(cur->prev_read, 0);
				if (cur->out != 1)
					dup2(cur->out, 1);
				else if (cur->next)
					dup2(cur->pipe_fd[1], 1);
				if (execve(cur->cmd[0], cur->cmd, NULL) == -1)
				{
					perror("exec failled\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (cur->prev_read)
					close(cur->prev_read);
				if (cur->in != 0)
					close(cur->in);
				if (cur->out != 1)
					close(cur->out);
				if (cur->next)
				{
					close(cur->pipe_fd[1]);
					cur->prev_read = cur->pipe_fd[0];
				}
			}
		}
		cur = cur->next;
	}
	cur = main->cmd;
	while (cur)
	{
		waitpid(cur->pid, NULL, 0);
		cur = cur->next;
	}
}

void	ft_creat_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		exit(EXIT_FAILURE);
		perror("pipe filled\n");
	}
}

void	ft_fork_process(t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}
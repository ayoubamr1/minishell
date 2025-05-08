/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:26 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/08 19:44:58 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commande(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_read;
	char	**path;
	
	cur = cmd;
	prev_read = 0;
	while (cur)
	{
		if (cur->next)
		{
			ft_creat_pipe(cmd);
			ft_fork_process(cmd);
			if (cmd->pid == 0) // child process
			{
				close(pipe_fd[0]);
				if (cur->in != 0)
					dup2(cur->in, 0);
				else if (prev_read)
					dup2(prev_read, 0);
				if (cur->out != 1)
					dup2(cur->out, 1);
				else if (cur->next)
					dup2(pipe_fd[1], 1);
				if (execve(cur->cmd[0], cur->cmd, NULL) == -1)
				{
					perror("exec failled\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (prev_read)
					close(prev_read);
				if (cur->next)
				{
					close(pipe_fd[1]);
					prev_read = pipe_fd[0];
				}
			}
		}
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
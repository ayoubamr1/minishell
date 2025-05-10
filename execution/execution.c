/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:26 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/10 18:05:31 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_commande(t_shell *main)
{
	t_cmd	*cur;
	char	**path;
	int		i;
	int		j;
	
	cur = main->cmd;
	cur->prev_read = 0;
	i = 0;
	j = 0;
	main->pid = malloc(main->nbr_cmd * sizeof(pid_t));
	if (!main->pid)
		exit(EXIT_FAILURE);
	printf("{%d}\n", main->nbr_cmd);
	while (cur)
	{
		if (cur->next)
			ft_creat_pipe(cur);
		ft_fork_process(main, i);
		if (main->pid[i] == 0) // child process
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
			if (cur->prev_read)
				close(cur->prev_read);
			if (cur->in != 0)
				close(cur->in);
			if (cur->out != 1)
				close (cur->out);
			if (cur->next)
			{
				close(cur->pipe_fd[0]);
				close(cur->pipe_fd[1]);
			}
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
		i++;
		cur = cur->next;
	}

	cur = main->cmd;
	while (j < main->nbr_cmd)
	{
		waitpid(main->pid[j], NULL, 0);
		j++;
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

void	ft_fork_process(t_shell *main, int i)
{
	main->pid[i] = fork();
	if (main->pid[i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}

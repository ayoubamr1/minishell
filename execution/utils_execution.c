/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:34:59 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/02 16:48:11 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_children(t_shell *main)
{
	int	i;
	
	i = 0;
	while (i < main->nbr_cmd)
	{
		if (waitpid(main->pid[i], NULL, 0) == -1)
			exit(1);
		i++;
	}
}

void ft_creat_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		perror("pipe filled\n");
		exit(EXIT_FAILURE);
	}
	// printf("{pipe 0 = %d pipe1 = %d}\n", cmd->pipe_fd[0], cmd->pipe_fd[1]);
}

void ft_fork_process(t_shell *main, int i)
{
	main->pid[i] = fork();
	if (main->pid[i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	// printf("forked pid[%d] : %d\n", i, main->pid[i]);
}

void	signal_hundler(int sig)
{
	write (1, "\nminishell>", 11);
}
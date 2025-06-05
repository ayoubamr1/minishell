/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:34:59 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/05 15:13:53 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_children(t_shell *main)
{
	int	i;
	int sig;
	int	status;
	
	i = 0;
	// status = 0;
	while (i < main->nbr_cmd)
	{
		if (waitpid(main->pid[i], &status, 0) == -1)
			exit(1);
		if (WIFEXITED(status))
			exite_status = WEXITSTATUS(status);
			// printf("childe exited with %d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{	
			
			sig = WTERMSIG(status);
			exite_status = 128 + sig;
			if (sig == SIGINT)
				write (1, "\n", 1);
			else if (sig == SIGQUIT)
				write (1, "Quit (core dumped)\n", 19);
			// printf("childe killed by signal %d\n", WTERMSIG(status));
		}
		i++;
	}
	// printf("exite_status = %d\n", exite_status);
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
	// exite_status = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, signal_hundler);
	signal(SIGQUIT, SIG_IGN);
}

void reset_signals_inshild(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
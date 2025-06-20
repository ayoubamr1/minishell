/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:34:59 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/19 14:16:01 by ayameur          ###   ########.fr       */
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
			ft_exit(main, main->cmd->cmd[0]);
		if (WIFEXITED(status))
			exite_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{	
			sig = WTERMSIG(status);
			exite_status = 128 + sig;
			if (sig == SIGINT)
				write (1, "\n", 1);
			else if (sig == SIGQUIT)
				write (1, "Quit (core dumped)\n", 19);
		}
		i++;
	}
}

void ft_creat_pipe(t_cmd *cmd)
{
	if (pipe(cmd->pipe_fd) == -1)
	{
		printf("{pipe 0 = %d pipe1 = %d}\n", cmd->pipe_fd[0], cmd->pipe_fd[1]);
		perror("pipe filled\n");
		exit(EXIT_FAILURE);
	}
}

void ft_fork_process(t_shell *main, int i)
{
	main->pid[i] = fork();
	if (main->pid[i] == -1)
	{
		printf("forked pid[%d] : %d\n", i, main->pid[i]);
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}

// void	signal_hundler(int sig)
// {
// 	write (1, "\nminishell>", 11);
	
// 	// exite_status = 130;
// }

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);      // Move to a new line
		rl_on_new_line();                  // Notify readline about the new line
		rl_replace_line("", 0);           // Clear the current input line
		rl_redisplay();                  // Redisplay the prompt
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void reset_signals_inshild(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

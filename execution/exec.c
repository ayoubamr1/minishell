/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:01:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/24 20:35:25 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_child(t_shell *main, t_cmd *cmd)
{
	// printf("in childe : in_fd = %d, out_fd = %d\n", cmd->in, cmd->out);
	close(cmd->pipe_fd[0]);
	if (cmd->out == -1337)
		cmd->out = cmd->pipe_fd[1];
	if (cmd->in != -1)
	{
		if (dup2(cmd->in, 0) == -1)
		{
			perror("dup2\n");
			exit(1);
		}
		close(cmd->in);
	}
	if (cmd->out != -1)
	{
		if (dup2(cmd->out, 1) == -1)
		{
			perror("dup2\n");
			exit(1);
		}
		close(cmd->out);
	}
	if (cmd->is_builtin == TRUE)
	{
		printf("is builtins : %s\n", cmd->cmd[0]);
		run_builtins(main, cmd->cmd, cmd);
		exit(1);
	}
	if (cmd->cmd && execve(cmd->cmd[0], cmd->cmd, env_in_2D(main)) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	ft_parent(t_shell *main, t_cmd *cmd)
{
	if (cmd->next)
	{
		close(cmd->pipe_fd[1]);
		if (cmd->next->in == -1337)
			cmd->next->in = cmd->pipe_fd[0];
	}
	close(cmd->in);
	close(cmd->out);
}

void flag_builtins(t_shell *main)
{
	t_cmd *curr;

	curr = main->cmd;
	while (curr)
	{
		if (curr->cmd && is_builtin(curr->cmd[0]))
			curr->is_builtin = TRUE;
		else
			curr->is_builtin = FALSE;

		curr = curr->next;
	}
}

void	execute_shild(t_shell *main)
{
	int		i;
	t_cmd	*cur;

	main->pid = malloc(main->nbr_cmd * sizeof(pid_t));
	if (main->pid == NULL)
		return;
	i = 0;
	cur = main->cmd;
	while (i < main->nbr_cmd && cur)
	{
		if (cur->next)
			ft_creat_pipe(cur);
		ft_fork_process(main, i);
		if (main->pid[i] == 0)
			ft_child(main, cur);
		else
			ft_parent(main, cur);
		// system("lsof -p $(echo $$)");
		cur = cur->next;
		i++;
	}
}

void exec_cmd(t_shell *main)
{
	int i;
	t_cmd *cur;

	i = 0;
	cur = main->cmd;
	
	if (cur->is_builtin && main->nbr_cmd == 1)
	{
		run_builtins(main, cur->cmd, cur);
		return;
	}
	execute_shild(main);
	wait_children(main);
}


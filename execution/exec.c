/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:01:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/18 14:20:58 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_dup_in(t_shell *main ,t_cmd *cmd)
{
	if (cmd->in != -1)
	{
		if (dup2(cmd->in, 0) == -1)
		{
			perror("dup2\n");
			exite_status = 1;
			if (main)
				cleanup(main, exite_status);
			ft_malloc(0, FREE);
			exit(exite_status);
		}
		close(cmd->in);
	}
}

void	child_dup_out(t_shell *main ,t_cmd *cmd)
{
	if (cmd->out != -1)
	{
		if (dup2(cmd->out, 1) == -1)
		{
			perror("dup2\n");
			exite_status = 1;
			if (main)
				cleanup(main, exite_status);
			ft_malloc(0, FREE);
			exit(exite_status);
		}
		close(cmd->out);
	}
}

void	execut_child_cmd(t_shell *main, t_cmd *cmd)
{
	// if (access(cmd->cmd[0], F_OK))
	// 	ft_exit(main, cmd->cmd[0]);
		// printf_error(cmd->cmd[0], "command not found", 127);
	if (cmd->cmd && execve(cmd->cmd[0], cmd->cmd, env_in_2D(main)) == -1)
	{
		ft_exit(main, cmd->cmd[0]);
		// perror("execve");
		// exite_status = 1;
		// if (main)
		// 	cleanup(main, exite_status);
		ft_malloc(0, FREE);
		exit(exite_status);
	}
}

void ft_child(t_shell *main, t_cmd *cmd)
{
	// printf("in childe : in_fd = %d, out_fd = %d\n", cmd->in, cmd->out);
	if (cmd->in == -1 || cmd->out == -1 || !cmd->cmd)
	{	
		cleanup(main, exite_status);
		// exit(exite_status);
		ft_malloc(0, FREE);
	}
	close(cmd->pipe_fd[0]);
	if (cmd->out == -1337)
		cmd->out = cmd->pipe_fd[1];
	child_dup_in(main, cmd);
	child_dup_out(main,cmd);

	if (cmd->is_builtin == TRUE)
	{
		// printf("is builtins : %s\n", cmd->cmd[0]);
		run_builtins(main, cmd->cmd, cmd);
		exit(exite_status);
	}
	execut_child_cmd(main, cmd);
	// reset_signals_inshild();
}

void	ft_parent(t_shell *main, t_cmd *cmd)
{
	// printf("in parent : in = %d out = %d\n", cmd->in, cmd->out);
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

	main->pid = ft_malloc(main->nbr_cmd * sizeof(pid_t), MALLOC);
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
			{	
				if (cur->fd_statuts == 1)
					exit(exite_status);
				ft_child(main, cur);
			}
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
	if (cur->is_builtin && main->nbr_cmd == 1 && cur->fd_statuts != 1)
	{
		main->saved_fdout = dup(1);
		main->saved_fdin = dup(0);
		if (cur->in != -1337)
			dup2(cur->in, 0);
		if (cur->out != -1337)
			dup2(cur->out, 1);
		run_builtins(main, cur->cmd, cur);
		dup2(main->saved_fdout, 1);
		close(main->saved_fdout);
		dup2(main->saved_fdin, 0);
		close(main->saved_fdin);
		return;
	}
	else
	{ 
		execute_shild(main);
		wait_children(main);
	}
}

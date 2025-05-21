/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:01:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/21 18:19:49 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_child(t_cmd *cmd, int read_fd, int write_fd, t_shell *main)
{
	// printf("in childe : read_fd = %d, write_fd = %d\n", read_fd, write_fd);
	if (read_fd != -1)
	{
		if (dup2(read_fd, 0) == -1)
			exit(1);
		close(read_fd);
	}
	if (write_fd != -1)	
	{	
		if (dup2(write_fd, 1) == -1)
			exit(1);
		close(write_fd);
	}
	if (cmd->is_builtin == TRUE)
	{
		printf("is builtins : %s\n", cmd->cmd[0]);
		run_builtins(main, cmd->cmd, cmd);
		exit(1);
	}
	// printf("is Not_builtins : %s\n", cmd->cmd[0]);
	if (execve(cmd->cmd[0], cmd->cmd, env_in_2D(main)) == -1)
	{
		perror("execve");
		exit(1);
	}
	// if (is_builtin(cmd[0]))
	// {
	// 	if (!strcmp(cmd[0], "env"))
	// 	{
	// 		printf("is builtins : %s\n", cmd[0]);
	// 		print_env(main);
	// 		exit(0);
	// 	}
	// 	else if (!strcmp(cmd[0], "cd"))
	// 	{
	// 		my_cd(cmd, main);
	// 		exit(0);
	// 	}
	// }
	// else
	// {
	// }
}

// int	is_builtin(t_shell *main)
// {
// 	t_cmd *cur;

// 	cur = main->cmd;
// 	if (!cur->is_builtin)
// 		return FALSE;
// 	return TRUE;
// }

void	flag_builtins(t_shell *main)
{
	t_cmd *curr;

	curr = main->cmd;
	while (curr)
	{
		// printf("cmd[0] = %s\n", curr->cmd[0]);
		// printf("cmd[0] = %p\n", curr->cmd[0]);
		if (!curr->cmd && curr->next->cmd)
		{
			pipe(curr->pipe_fd);
			// printf("pipe[0] = %d\n", curr->pipe_fd[0]);
			// printf("pipe[1] = %d\n", curr->pipe_fd[1]);
			close(curr->pipe_fd[1]);
			curr->next->in = curr->pipe_fd[0];
			// printf("in_fd = %d\n", curr->in);
			curr = curr->next;
		}
		if (is_builtin(curr->cmd[0])) // curr && curr->cmd[0] && 
			curr->is_builtin = TRUE;
		else
			curr->is_builtin = FALSE;
		
		curr = curr->next;
	}
}

// void	flag_builtins(t_shell *main)
// {
// 	t_cmd *curr;

// 	curr = main->cmd;
// 	while (curr)
// 	{
// 		if (!ft_strcmp(curr->cmd[0], "env") || !ft_strcmp(curr->cmd[0], "cd")
// 			|| !ft_strcmp(curr->cmd[0], "export") || !ft_strcmp(curr->cmd[0], "pwd")
// 			|| !ft_strcmp(curr->cmd[0], "unset"))
// 			curr->is_builtin = TRUE;
// 		else
// 			curr->is_builtin = FALSE;
		
// 		curr = curr->next;
// 	}
// }

void	exec_cmd(t_shell *main)
{
	int		i;
	int		j;
	t_cmd	*cur;

	i = 0;
	j = 0;
	cur = main->cmd;
	nbr_cmd(main);
	get_path(main);
	flag_builtins(main);
	check_if_access(main);
	// main->nbr_cmd = ft_lstsize_cmd(main->cmd);
	// printf("in_fd = %d\n", main->cmd->in);
	// printf("out_fd = %d\n", main->cmd->out);
	main->pid = malloc(main->nbr_cmd * sizeof(pid_t));
	if (main->pid == NULL)
		return ;
	main->in_fd = main->cmd->in;
	if (cur->is_builtin && main->nbr_cmd == 1)
	{
		run_builtins(main, cur->cmd, cur);
		return ;
	}
	while (i < main->nbr_cmd && cur)
	{
		// printf("==================\n");
		if (cur->next)
			ft_creat_pipe(cur);
		ft_fork_process(main, i);
		if (main->pid[i] == 0)
		{
			// rintf("child process %d\n", i);
			// rintf("==================\n");
			// f (!cur->cmd || !cur->cmd[0])
			
			// printf("cur->cmd[0] is NULL\n");
			// exit(1);
			
			// rintf("==================\n");
			// rintf("will exec: %s\n", cur->cmd[0]);
			// xit(0);
			if (cur->next)
			{
				close(cur->pipe_fd[0]);
				ft_check_child(cur, main->in_fd, cur->pipe_fd[1], main);
			}
			else
				ft_check_child(cur, main->in_fd, cur->out, main);
		}
		else
		{
			if (cur->next)
				close(cur->pipe_fd[1]);
			if (main->in_fd != 0)
			{	
				printf("closing leftover in_fd = %d\n", main->in_fd);
				close(main->in_fd);
			}
			if (cur->next)
				main->in_fd = cur->pipe_fd[0];
		}
		// system("lsof -p $(echo $$)");
		cur = cur->next;
		i++;
	}
	while (j < main->nbr_cmd)
	{
		if (waitpid(main->pid[j], NULL, 0) == -1)
			exit(1);
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
	// printf("{pipe 0 = %d pipe1 = %d}\n", cmd->pipe_fd[0], cmd->pipe_fd[1]);
}

void	ft_fork_process(t_shell *main, int i)
{
	main->pid[i] = fork();
	if (main->pid[i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	// printf("forked pid[%d] : %d\n", i, main->pid[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:01:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/12 16:37:12 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_child(char **cmd, int read_fd, int write_fd)
{
	printf("in childe : read_fd = %d, write_fd = %d\n", read_fd, write_fd);
	if (read_fd != -1)
	{
		if (dup2(read_fd, 0) == -1)
			exit(1);
	}
	// close(read_fd);
	if (write_fd != -1)	
	{	
		if (dup2(write_fd, 1) == -1)
			exit(1);
	}
	// close(write_fd);
	// if (fcntl(1, F_GETFD) == -1)
    // 	perror("stdout is closed");
	// else
    // 	printf("stdout is open\n");
	printf("{cmd = %s}\n", cmd[0]);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	exec_cmd(t_shell *main)
{
	int		i;
	int		j;
	t_cmd	*cur;
	t_cmd	*tmp;
	
	tmp = main->cmd;
	while (tmp)
	{
		printf("{%s}\n", tmp->cmd[0]);
		tmp = tmp->next;
	}
	printf("numbre of commande %d\n", main->nbr_cmd);
	i = 0;
	j = 0;
	cur = main->cmd;
	printf("in_fd = %d\n", main->cmd->in);
	printf("out_fd = %d\n", main->cmd->out);
	main->in_fd = main->cmd->in;
	main->pid = malloc(main->nbr_cmd * sizeof(pid_t));
	if (main->pid == NULL)
		return ;
	while (i < main->nbr_cmd && cur)
	{
		printf("==================\n");
		if (cur->next)
			ft_creat_pipe(cur);
		ft_fork_process(main, i);
		if (main->pid[i] == 0)
		{
			printf("child process %d\n", i);
			printf("==================\n");
			if (!cur->cmd || !cur->cmd[0])
			{
				printf("cur->cmd[0] is NULL\n");
				exit(1);
			}
			printf("==================\n");
			printf("will exec: %s\n", cur->cmd[0]);
			// exit(0);
			if (cur->next)
			{	
				close(cur->pipe_fd[0]);
				ft_check_child(cur->cmd, main->in_fd, cur->pipe_fd[1]);
			}
			else
				ft_check_child(cur->cmd, main->in_fd, cur->out);
		}
		else
		{	
			if (cur->next)
				close(cur->pipe_fd[1]);
			if (main->in_fd != 0)
				close(main->in_fd);
			if (cur->next)
				main->in_fd = cur->pipe_fd[0];
			// close(cur->pipe_fd[1]), close(main->in_fd),
					// main->in_fd = cur->pipe_fd[0];
		}
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
	printf("{pipe 0 = %d pipe1 = %d}\n", cmd->pipe_fd[0], cmd->pipe_fd[1]);
}

void	ft_fork_process(t_shell *main, int i)
{
	main->pid[i] = fork();
	if (main->pid[i] == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	printf("forked pid[%d] : %d\n", i, main->pid[i]);
}

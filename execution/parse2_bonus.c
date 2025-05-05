/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:21:07 by ayameur           #+#    #+#             */
/*   Updated: 2025/04/14 15:50:26 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_check_cmds_path(t_pipex_bonus *pipex)
{
	int		i;

	i = 0;
	while (pipex->command_array[i])
	{
		if (access(pipex->command_array[i][0], X_OK | F_OK) == 0)
			i++;
		else
		{
			ft_check_command_in_path(pipex, i);
			i++;
		}
	}
}

void	ft_check_command_in_path(t_pipex_bonus *pipex, int i)
{
	int		j;
	char	*result;
	char	*tmp;

	j = 0;
	result = NULL;
	while (pipex->path_env[j])
	{
		tmp = ft_strjoin(pipex->path_env[j], "/");
		if (tmp == NULL)
			free_previous(pipex);
		result = ft_strjoin(tmp, pipex->command_array[i][0]);
		if (result == NULL)
			(free_2d(pipex->path_env), free_command_array(pipex->command_array),
				close_fds(pipex), free(tmp));
		free(tmp);
		if (access(result, X_OK | F_OK) == 0)
		{
			free(pipex->command_array[i][0]);
			pipex->command_array[i][0] = result;
			break ;
		}
		free(result);
		j++;
	}
}

void	ft_check_child(t_pipex_bonus *pipex, int read_fd, int write_fd, int i)
{
	if (dup2(read_fd, 0) == -1)
		(ft_putstr_fd("Error7\n", 2), free_command_array(pipex->command_array),
			cleanup_pid(pipex), free_2d(pipex->path_env), exit(1));
	close(read_fd);
	if (dup2(write_fd, 1) == -1)
		(ft_putstr_fd("Error8\n", 2), free_command_array(pipex->command_array),
			cleanup_pid(pipex), free_2d(pipex->path_env), exit(1));
	close(write_fd);
	if (execve(pipex->command_array[i][0], pipex->command_array[i], NULL) == -1)
	{
		free_command_array(pipex->command_array);
		free_2d(pipex->path_env);
		cleanup_pid(pipex);
		if (write_fd == pipex->p[1])
			close(pipex->outfile_fd);
		else if (write_fd == pipex->outfile_fd)
			close(pipex->p[1]);
		perror("execve");
		exit(1);
	}
}

void	ft_execute_cmds(t_pipex_bonus *pipex)
{
	int	i;

	i = 0;
	pipex->in_fd = pipex->infile_fd;
	pipex->pid = malloc(pipex->nbr_cmd * sizeof(int));
	if (pipex->pid == NULL)
		(ft_putstr_fd("Error\n", 2), free_command_array(pipex->command_array),
			free_2d(pipex->path_env), close_fds(pipex), exit(1));
	while (i < pipex->nbr_cmd)
	{
		ft_creat_pipe(pipex);
		ft_fork_process(pipex, i);
		if (pipex->pid[i] == 0)
		{
			close(pipex->p[0]);
			if (i != pipex->nbr_cmd - 1)
				ft_check_child(pipex, pipex->in_fd, pipex->p[1], i);
			else
				ft_check_child(pipex, pipex->in_fd, pipex->outfile_fd, i);
		}
		else
			(close(pipex->p[1]), close(pipex->in_fd),
				pipex->in_fd = pipex->p[0], i++);
	}
	ft_wait_for_children(pipex);
}

void	ft_creat_pipe(t_pipex_bonus *pipex)
{
	if (pipe(pipex->p) == -1)
	{
		ft_putstr_fd("Error9\n", 2);
		free_command_array(pipex->command_array);
		cleanup_pid(pipex);
		free_2d(pipex->path_env);
		close_fds(pipex);
		exit(1);
	}
}

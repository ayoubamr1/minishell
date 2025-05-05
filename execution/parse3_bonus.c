/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:49:46 by ayameur           #+#    #+#             */
/*   Updated: 2025/03/14 20:53:08 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_fork_process(t_pipex_bonus *pipex, int i)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
	{	
		ft_putstr_fd("Error10\n", 2);
		free_command_array(pipex->command_array);
		cleanup_pid(pipex);
		free_2d(pipex->path_env);
		close_fds(pipex);
		exit(1);
	}
}

void	ft_wait_for_children(t_pipex_bonus *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		if (waitpid(pipex->pid[i], NULL, 0) == -1)
		{
			ft_putstr_fd("Error10\n", 2);
			free_command_array(pipex->command_array);
			cleanup_pid(pipex);
			free_2d(pipex->path_env);
			exit(1);
		}
		i++;
	}
	close(pipex->outfile_fd);
	close(pipex->in_fd);
}

void	free_previous(t_pipex_bonus *pipex)
{
	free_2d(pipex->path_env);
	free_command_array(pipex->command_array);
}

void	close_fds(t_pipex_bonus *pipex)
{
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
}

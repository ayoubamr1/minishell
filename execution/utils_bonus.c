/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:53:35 by ayameur           #+#    #+#             */
/*   Updated: 2025/03/14 20:53:16 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_array(t_pipex_bonus *pipex)
{
	free_command_array(pipex->command_array);
	free_2d(pipex->path_env);
	cleanup_pid(pipex);
}

void	free_command_array(char ***cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array[i])
	{
		free_2d(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}

void	cleanup_pid(t_pipex_bonus *pipex)
{
	if (pipex->pid)
		free(pipex->pid);
	pipex->pid = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

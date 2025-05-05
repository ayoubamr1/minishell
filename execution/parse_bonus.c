/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:35:00 by ayameur           #+#    #+#             */
/*   Updated: 2025/03/17 02:16:36 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	count_cmd(t_pipex_bonus *pipe, int ac)
{
	pipe->nbr_cmd = ac - 3;
}

void	ft_open_files(t_pipex_bonus *pipex, char *infile, char *outfile)
{
	if (pipex->here_doc)
	{	
		pipex->outfile_fd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (pipex->outfile_fd == -1)
			(ft_putstr_fd("Error2 in opening outfile\n", 2), exit(1));
	}
	else
	{
		pipex->infile_fd = open(infile, O_RDONLY);
		if (pipex->infile_fd == -1)
			(ft_putstr_fd("Error2 in opening infile\n", 2), exit(1));
		pipex->outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->outfile_fd == -1)
			(ft_putstr_fd("Error3 in opening outfile\n", 2),
				close(pipex->infile_fd), exit(1));
	}
}

char	**get_path(char **env)
{
	char	**result;
	char	*path_string;

	path_string = NULL;
	while (*env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
		{
			path_string = *env;
			break ;
		}
		(env++);
	}
	if (path_string == NULL)
		return (NULL);
	if (*(path_string + 5) == '\0')
		return (NULL);
	result = ft_split(path_string + 5, ':');
	return (result);
}

void	ft_init_pipex(int ac, char **av, char **env, t_pipex_bonus *pipex)
{
	int		i;

	pipex->command_array = NULL;
	i = 0;
	ft_open_files(pipex, av[1], av[ac - 1]);
	pipex->path_env = get_path(env);
	if (pipex->path_env == NULL)
		(ft_putstr_fd("Error4\n", 2), close_fds(pipex), exit(1));
	pipex->command_array = malloc((pipex->nbr_cmd + 1) * sizeof(char **));
	if (pipex->command_array == NULL)
		(ft_putstr_fd("Error5\n", 2), free_2d(pipex->path_env), close_fds(pipex),
			exit(1));
	while (i < pipex->nbr_cmd)
	{
		pipex->command_array[i] = ft_split(av[i + 2 + pipex->here_doc], ' ');
		if (pipex->command_array[i] == NULL)
			(ft_putstr_fd("Error6\n", 2), free_2d(pipex->path_env),
				close_fds(pipex), exit(1));
		i++;
	}
	pipex->command_array[i] = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:24:53 by ayameur           #+#    #+#             */
/*   Updated: 2025/03/14 21:34:00 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipex_bonus	pipex;

	if (ac < 5)
		return (ft_putstr_fd("Error1\n", 2), 1);
	pipex.here_doc = 0;
	count_cmd(&pipex, ac);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		pipex.here_doc = 1;
		hundle_here_doc(&pipex, av[2]);
		pipex.nbr_cmd = ac - 4;
	}
	ft_init_pipex(ac, av, env, &pipex);
	ft_check_cmds_path(&pipex);
	ft_execute_cmds(&pipex);
	free_array(&pipex);
}

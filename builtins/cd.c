/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:13:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/19 20:28:02 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_target_dir(char **str, t_shell *main)
{
	char	*target_dir;

	if (str[1])
		target_dir = str[1];
	else
	{
		target_dir = my_getenv(main, "HOME");
		if (target_dir == NULL)
		{
			perror("cd\n");
			return (NULL);
		}
	}
	return (target_dir);
}

int	change_dir(char *target_dir, char **oldpwd, char **newpwd)
{
	*oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		free(oldpwd);
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	*newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cwd");
		free(oldpwd);
		return (1);
	}
	return (0);
}

void	update_dir_env(t_shell *main, char *oldpwd, char *newpwd)
{
	update_env(main, "OLDPWD", oldpwd);
	update_env(main, "PWD", newpwd);
}

int	my_cd(char **str, t_shell *main)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target_dir;

	target_dir = get_target_dir(str, main);
	if (!target_dir)
		return (1);
	if (change_dir(target_dir, &oldpwd, &newpwd) != 0)
		return (1);
	update_dir_env(main, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

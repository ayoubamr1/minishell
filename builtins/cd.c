/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:13:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/14 16:42:32 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int exit_status = 0;

int	my_cd(char **str, t_shell *main)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target_dir;
	
	if (str[1])
		target_dir = str[1];
	else
	{
		target_dir = my_getenv(main,"HOME");
		// printf("{taget_dir in my env %s}\n", target_dir);
		if (target_dir == NULL)
		{
			perror("cd\n");
			return (1);
		}
	}
	// printf("{%s}\n", target_dir);
	// get the currect working directory
	oldpwd = getcwd(NULL, 0);
	// printf("{cwd = %s}\n", oldpwd);
	if (!oldpwd)
	{
		perror("getcwd");
		free(oldpwd);
		// exite_status = 1;
		return (1);
	}
	// change directory
	// printf("=======================\n");
	if (chdir(target_dir) != 0)
	{
		// printf("======== dkhal hna ======");
		// printf("{%s}\n", target_dir);
		perror("cd");
		free(oldpwd);
		return (1);
	}
	// it still update PWD in my environment variable
	// printf("cwd = %s\n", cwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cwd");
		free(oldpwd);
		return (1);
	}
	update_env(main, "OLDPWD", oldpwd); // OLDPWD become cwd
	update_env(main, "PWD", newpwd); // PWD become target_dir
	free(oldpwd);
	free(newpwd);
	// printf("target_dir = %s\n", target_dir);
	return (0);
	
}

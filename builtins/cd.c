/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:13:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/14 12:29:48 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_cd(char **str, t_shell *main)
{
	char	*cwd;
	char	*target_dir;
	t_env	*env;
	
	// env = main->env;
	if (str[1])
	{	
		target_dir = str[1];
	}
	else
	{
		target_dir = my_getenv(env,"HOME");
		printf("{taget_dir in my env %s}\n", target_dir);
		if (target_dir == NULL)
		{
			perror("cd\n");
			return (1);
		}
	}
	printf("{%s}\n", target_dir);
	// get the currect working directory
	cwd = getcwd(NULL, 0);
	printf("{cwd = %s}\n", cwd);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	// change directory
	printf("=======================\n");
	if (chdir(target_dir) != 0)
	{
		printf("======== dkhal hna ======");
		printf("{%s}\n", target_dir);
		perror("cd");
		return (1);
	}
	// it still update PWD in my environment variable
	update_env(main->env, cwd); // OLDPWD become cwd
	printf("====== hna error =======\n");
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cwd");
		return (1);
	}
	update_env(main->env, target_dir); // PWD become target_dir
	free(cwd);
	return (0);
	// if (setenv("PWD", target_dir, 1) != 0)
	// {
	// 	perror("setenv");
	// 	return (1);
	// }
}

int main ()
{
	// char *arr[] = {"cd", "echo", "export", "unset", NULL};
	char *arr[] = {"cd", "/tmp" , NULL};
	int i;
	t_shell *main;
	i = 0;
	while (arr[i] != NULL)
	{
		if (strcmp(arr[i], "cd") == 0)
			my_cd(arr, main);
		// else if ((strcmp(arr[i][j], "echo") == 0))
		// 	my_echo(arr);
		// else if	(strcmp(arr[i][j], "export") == 0)
		// 	my_export(arr);
		// else if (strcmp(arr[i][j], "unset") == 0)
		// 	my_unset(arr);
		i++;
	}
}
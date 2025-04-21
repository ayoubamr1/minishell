/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:13:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/04/21 15:03:37 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_cd(char **str)
{
	char	*cwd;
	char	*target_dir;
	
	target_dir = str[1];
	// get the currect working directory
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	if (target_dir == NULL)
	{
		target_dir = getenv("HOME");
		if (target_dir == NULL)
		{
			perror("cd\n");
			return (1);
		}
	}
	// change directory
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	if (setenv("PWD", target_dir, 1) != 0)
	{
		perror("setenv");
		return (1);
	}
}

int main ()
{
	char *arr[] = {"cd", "echo", "export", "unset", NULL};
	int i;
	i = 0;
	while (arr[i] != NULL)
	{
		if (strcmp(arr[i], "cd") == 0)
				my_cd(arr);
		// else if ((strcmp(arr[i][j], "echo") == 0))
		// 	my_echo(arr);
		// else if	(strcmp(arr[i][j], "export") == 0)
		// 	my_export(arr);
		// else if (strcmp(arr[i][j], "unset") == 0)
		// 	my_unset(arr);
		i++;
	}
}
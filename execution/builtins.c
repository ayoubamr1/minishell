/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/19 13:23:27 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env(t_shell *main){
	t_env *env = main->env;
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

void	run_builtins(t_shell *main, char **cmd)
{
	// puts(cmd->cmd[0]);
	if (!ft_strcmp(cmd[0], "cd"))
		my_cd(cmd, main);
	if (!ft_strcmp(cmd[0], "env"))
		print_env(main);
	if (!ft_strcmp(cmd[0], "export"))
		my_export(main, cmd[1]);
	if (!ft_strcmp(cmd[0], "pwd"))
		my_pwd(main);
	if (!ft_strcmp(cmd[0], "unset"))
		unset_env(main, cmd[1]);
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "export") || 
		!ft_strcmp(str, "pwd") || !ft_strcmp(str, "echo"))
		return TRUE;
	return FALSE;
}
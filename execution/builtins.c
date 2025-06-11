/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/11 11:46:10 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtins(t_shell *main, char **cmd, t_cmd *cur)
{
	// puts(cmd->cmd[0]);
	if (!ft_strcmp(cmd[0], "cd"))
		exite_status = my_cd(cmd, main);
	if (!ft_strcmp(cmd[0], "env"))
		exite_status = print_env(main);
	if (!ft_strcmp(cmd[0], "export"))
		exite_status = my_export(main, cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		exite_status = my_pwd(main);
	if (!ft_strcmp(cmd[0], "unset"))
		exite_status = unset_env(main, cmd);
	if (!ft_strcmp(cmd[0], "echo"))
	{
		if (cmd[1] && ft_strcmp(cmd[1], "$?") == 0)
		{
			printf("%d\n", exite_status);
			exite_status = 0;
			return ;
		}
		// else
		exite_status = my_echo(cmd, cur);
		// exite_status = 0;
	}	
	if (!ft_strcmp(cmd[0], "exit"))
		exite_status = my_exit(main, cmd);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "export") || 
		!ft_strcmp(str, "pwd") || !ft_strcmp(str, "echo")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "exit"))
		return TRUE;
	return FALSE;
}

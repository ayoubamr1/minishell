/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/04 18:04:16 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtins(t_shell *main, char **cmd, t_cmd *cur)
{
	// puts(cmd->cmd[0]);
	if (!ft_strcmp(cmd[0], "cd"))
		exite_status = my_cd(cmd, main);
	if (!ft_strcmp(cmd[0], "env"))
		print_env(main);
	if (!ft_strcmp(cmd[0], "export"))
		my_export(main, cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		my_pwd(main);
	if (!ft_strcmp(cmd[0], "unset"))
		unset_env(main, cmd[1]);
	if (!ft_strcmp(cmd[0], "echo"))
		my_echo(cmd, cur);
	if (!ft_strcmp(cmd[0], "exit"))
		my_exite(main);
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

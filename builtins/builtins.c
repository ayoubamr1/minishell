/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:48 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/14 20:16:40 by ayameur          ###   ########.fr       */
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

int	builtins(t_shell *main, t_cmd *cmd)
{
	// puts(cmd->cmd[0]);
	if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		return (my_cd(cmd->cmd, main), 1);
	if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
		return (print_env(main), 1);
	// if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	// if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
	return 0;
} 
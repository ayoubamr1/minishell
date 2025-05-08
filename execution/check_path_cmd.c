/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:02 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/08 19:41:53 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_path(t_shell *main)
{
	t_env	*cur;
	char	*path;

	cur = main->env;
	while (cur)
	{
		if (ft_strncmp(cur->content, "PATH=", 5) == 0)
		{
			path = cur->content;
			break ;
		}
		cur = cur->next;
	}
	if (path == NULL)
		return ;
	if (*(path + 5) == '\0')
		return ;
	cur->path_splited = ft_split(path, ':');
}

void	check_if_access(t_shell *main)
{
	t_cmd	*cmd;
	t_env	*env;

	cmd = main->cmd;
	env = main->env;
	while (cmd)
	{
		if (access(cmd->cmd[0], X_OK | F_OK) == 0)
			cmd = cmd->next;
		else
		{
			ft_check_cmd_path(cmd, env);
			cmd = cmd->next;
		}
	}
}

void	ft_check_cmd_path(t_cmd	*cmd_array, t_env *env)
{
	int		j;
	char	*res;
	char	*tmp;
	t_cmd	*cur;
	
	j = 0;
	cur = cmd_array;
	while (cur->cmd[j])
	{
		tmp = ft_strjoin(env->path_splited[j], "/");
		if (!tmp)
			return ; /// free leaks
		res = ft_strjoin(tmp, cur->cmd[0]);
		if (!res)
			return ; /// free leaks;
		free(tmp);
		if (access(res, X_OK | F_OK) == 0)
		{
			free(cur->cmd[0]);
			cur->cmd[0] = res;
			break ;
		}
		free(res);
		j++;
	}
}

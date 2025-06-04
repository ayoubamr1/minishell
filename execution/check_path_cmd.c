/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:02 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/02 17:29:53 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_path(t_shell *main)
{
	t_env	*cur;
	char	*path;

	cur = main->env;
	path = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->content, "PATH=", 5) == 0)
		{
			path = cur->content + 5;
			break ;
		}
		cur = cur->next;
	}
	if (path == NULL || *(path + 5) == '\0')
	{	
		printf("commande not found\n");
		main->path_splited = NULL;
		// exit(1);
		return ;
	}
	// if (*(path + 5) == '\0')
	// {
	// 	// exit(1);
	// 	return ;
	// }
	// printf("my path = %s\n", path);
	main->path_splited = ft_split(path, ':');
}

void	check_if_access(t_shell *main)
{
	t_cmd	*cmd;
	t_env	*env;

	cmd = main->cmd;
	env = main->env;

	while (cmd)
	{
		if (cmd->is_builtin)
			cmd = cmd->next;
		else
		{
			if (cmd->cmd && cmd->cmd[0] && access(cmd->cmd[0], X_OK | F_OK) == 0)
				cmd = cmd->next;
			else
			{
				ft_check_cmd_path(cmd, main->path_splited);
				cmd = cmd->next;
			}
		}
	}
}

void	ft_check_cmd_path(t_cmd *cmd, char **path)
{
	int		i;
	char	*res;
	char	*tmp;
	t_cmd	*cur;
	
	i = 0;
	cur = cmd;
	while (path && path[i] && cur->cmd)
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return ; /// free leaks
		res = ft_strjoin(tmp, cur->cmd[0]);
		if (!res)
			return ; /// free leaks;
		// free(tmp);
		// printf("res = %s\n", res);
		if (access(res, X_OK | F_OK) == 0)
		{
			// free(cur->cmd[0]);
			cur->cmd[0] = res;
			break ;
		}
		// free(res);
		i++;
	}
}

void	nbr_cmd(t_shell *main)
{
	t_cmd	*cur;
	int		count;

	cur= main->cmd;
	count = 0;
	while (cur)
	{
		// printf("commande : %s\n", cur->cmd[0]);
		count++;
		cur = cur->next;
	}
	// printf("final count %d\n", count);
	main->nbr_cmd = count;
}
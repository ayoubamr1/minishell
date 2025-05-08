/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:33:02 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/08 13:53:16 by ayameur          ###   ########.fr       */
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
		return (NULL);
	if (*(path + 5) == '\0')
		return (NULL);
	cur->path_splited = ft_split(path, ':');
}

void	check_if_access(t_shell *main)
{
	t_cmd	*cmd;
	t_env	*env;
	int		i;

	i = 0;
	cmd = main->cmd;
	env = main->env;
	while (cmd)
	{
		if (access(cmd->cmd[i], X_OK | F_OK) == 0)
			i++;
		else
		{
			ft_check_cmd_path(cmd->cmd, env, i);
			i++;
		}
		cmd = cmd->next;
	}
}

void	ft_check_cmd_path(char	**cmd_array, t_env *env, int i)
{
	int		j;
	char	*res;
	char	*tmp;
	
	j = 0;
	while (cmd_array[j])
	{
		tmp = ft_strjoin(env->path_splited[j], "/");
		if (!tmp)
			return (NULL); /// free leaks
		res = ft_strjoin(tmp, cmd_array[j]);
		if (!res)
			return (NULL); /// free leaks;
		free(tmp);
		if (access(res, X_OK | F_OK) == 0)
		{
			free(cmd_array[i]);
			cmd_array[i] = res;
			break ;
		}
		free(res);
		j++;
	}
}

void	execute_commande(t_cmd *cmd, t_env *env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_read;
	char	**path;
	
	cur = cmd;
	prev_read = 0;
	while (cur)
	{
		if (cur->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe filled\n");
				exit(EXIT_FAILURE);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			if (pid == 0) // child process
			{
				if (cur->in != 0)
					dup2(cur->in, 0);
				else if (prev_read)
					dup2(prev_read, 0);
				if (cur->out != 1)
					dup2(cur->out, 1);
				else if (cur->next)
					dup2(pipe_fd[1], 1);
				if (execve(cur->cmd[0], cur->cmd, env->content) == -1)
				{
					perror("exec failled\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (prev_read)
					close(prev_read);
				if (cur->next)
				{
					close(pipe_fd[1]);
					prev_read = pipe_fd[0];
				}
			}
		}
		cur = cur->next;
	}
}
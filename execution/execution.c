/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:26 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/14 18:07:26 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_shell *main)
{
	t_cmd *tmp;

	tmp = main->cmd;
	while (tmp)
	{
		if (tmp->heredoc_statuts == 911)
			return;
		tmp = tmp->next;
	}
	nbr_cmd(main);
	get_path(main);
	check_redir(main);
	flag_builtins(main);
	check_if_access(main);
	// edit_redir(main);
	// print_node(main, NULL);
	// hundle_shlvl(main);
	exec_cmd(main);
}

void	hundle_shlvl(t_shell *main)
{
	t_env *curr;
	t_cmd *cmd;
	char	*new_shlvl;

	curr = main->env;
	cmd = main->cmd;
	if (cmd->cmd && cmd && !ft_strcmp(cmd->cmd[0], "./minishell"))
	{
		while (curr)
		{
			if (!ft_strncmp(curr->content, "SHLVL=", 6))
			{
				new_shlvl = ft_itoa(ft_atoi(curr->content + 6) + 1);
				free(curr->content);
				curr->content = ft_strjoin("SHLVL=", new_shlvl);
				break ;
			}
			curr = curr->next;
		}
	}
}

// void edit_redir(t_shell *main)
// {
// 	t_cmd *curr;

// 	curr = main->cmd;
// 	while (curr)
// 	{
// 		if (curr == main->cmd && !curr->next)
// 		{
// 			if (curr->in == -1)
// 				curr->in = open("/dev/stdin", O_RDONLY);
// 			if (curr->out == -1)
// 				curr->out = open("/dev/stdout", O_RDWR);
// 			return ;
// 		}
// 		if (curr == main->cmd)
// 		{
// 			if (curr->in == -1)
// 				curr->in = open("/dev/stdin", O_RDONLY);
// 			if (curr->out == -1)
// 				curr->out = -1337;
// 		}
// 		if (curr != main->cmd && curr->next)
// 		{
// 			if (curr->in == -1)
// 				curr->in = -1337;
// 			if (curr->out == -1)
// 				curr->out = -1337;
// 		}
// 		if (curr != main->cmd && !curr->next)
// 		{
// 			if (curr->in == -1)
// 				curr->in = -1337;
// 			if (curr->out == -1)
// 			{	
// 				curr->out = open("/dev/stdout", O_RDWR);
// 			}
// 		}
// 		curr = curr->next;
// 	}
// }

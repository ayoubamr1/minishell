/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:48:26 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/25 18:52:47 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_shell *main)
{
	nbr_cmd(main);
	get_path(main);
	check_redir(main);
	flag_builtins(main);
	check_if_access(main);
	edit_redir(main);
	print_node(main, NULL);
	exec_cmd(main);
}

void edit_redir(t_shell *main)
{
	t_cmd *curr;

	curr = main->cmd;
	while (curr)
	{
		if (curr == main->cmd && !curr->next)
		{
			if (curr->in == -1)
				curr->in = open("/dev/stdin", O_RDONLY);
			if (curr->out == -1)
				curr->out = open("/dev/stdout", O_RDWR);
			return ;
		}
		if (curr == main->cmd)
		{
			if (curr->in == -1)
				curr->in = open("/dev/stdin", O_RDONLY);
			if (curr->out == -1)
				curr->out = -1337;
		}
		if (curr != main->cmd && curr->next)
		{
			if (curr->in == -1)
				curr->in = -1337;
			if (curr->out == -1)
				curr->out = -1337;
		}
		if (curr != main->cmd && !curr->next)
		{
			if (curr->in == -1)
				curr->in = -1337;
			if (curr->out == -1)
				curr->out = open("/dev/stdout", O_RDWR);
		}
		curr = curr->next;
	}
}

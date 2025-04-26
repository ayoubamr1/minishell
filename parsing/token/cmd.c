/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/26 18:21:13 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_redir_in(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_RDONLY);
	if (fd < 0)
		perror(start->content);
	node->file = ft_strdup(start->content);
	close(node->in);
	node->in = fd;
	return (start->next);
}

static t_token	*handle_redir_out(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		perror(start->content);
	node->file = ft_strdup(start->content);
	close(node->out);
	node->out = fd;
	return (start->next);
}

static t_token	*handle_redir_append(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		perror(start->content);
	node->file = ft_strdup(start->content);
	close(node->out);
	node->out = fd;
	return (start->next);
}

static t_token	*store_cmd_node(t_cmd *node_to_fill, t_token *start)
{
	if (!start)
		return (NULL);
	while (start && start->type != PIPE)
	{
		if (start->type == WORD || start->type == STRING)
		{
			node_to_fill->args = ft_strjoin2d(node_to_fill->args, start->content);
			start = start->next;
		}
		else if (start && start->type == REDIR_IN)
			start = handle_redir_in(node_to_fill, start);
		else if (start && start->type == REDIR_OUT)
			start = handle_redir_out(node_to_fill, start);
		else if (start && start->type == APPEND)
			start = handle_redir_append(node_to_fill, start);
		// else if (start && start->type == HEREDOC)
		// 	start = handle_heredoc(node_to_fill, start); // nooe_to_fill == hi lirt3mare  && start hiya li radi takhod manha
	}
	return (start);
}
t_cmd	*ft_cmd(t_token **token, t_cmd **cmd_list)
{
	t_token	*tmp;
	t_cmd	*head;
	t_cmd	*cmd_tmp;

	tmp = *token;
	cmd_tmp = ft_lstnew_cmd();
	head = cmd_tmp;
	ft_lstadd_back_cmd(cmd_list, cmd_tmp);
	while (tmp)
	{
		tmp = store_cmd_node(cmd_tmp, tmp);
		if (tmp && tmp->type == PIPE)
		{
			cmd_tmp = ft_lstnew_cmd();
			ft_lstadd_back_cmd(cmd_list, cmd_tmp);
			tmp = tmp->next;
		}
	}
	return (head);
}

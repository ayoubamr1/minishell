/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/06 18:19:49 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_token *store_cmd_node(t_shell *shell, t_cmd *node_to_fill, t_token *start)
{
	
	if (!start)
	return (NULL);
	while (start && start->type != PIPE)
	{
		if (start->type == HEREDOC)
			start = handle_heredoc_token(shell, node_to_fill, start);
		else
			start = process_token_type(node_to_fill, start);
		if (node_to_fill->fd_statuts == 1)
		{
			while (start && start->type != PIPE)
				start = start->next;
			break;
		}
	}
	return (start);
}

t_token *process_token_type(t_cmd *node, t_token *start)
{
	char **spl;

	if (start->type == WORD || start->type == SI_QUOTE)
	{
		// spl = ft_split(start->content, ' ');
		// node->cmd = ft_join2d(node->cmd, spl);
		node->cmd = ft_strjoin2d(node->cmd, start->content);
		return (start->next);
	}
	else if (start->type == REDIR_IN)
		return handle_redir_in(node, start);
	else if (start->type == REDIR_OUT)
		return handle_redir_out(node, start);
	else if (start->type == APPEND)
		return handle_redir_append(node, start);
	return start->next;
}

t_token *handle_heredoc_token(t_shell *shell, t_cmd *node, t_token *start)
{
	int		fd[2];
	char	*filepath;

	start = start->next;
	if (!start || !start->content || start->content[0] == '\0')
		start = new_token(ft_strdup(""), HEREDOC);	
	filepath = ft_strjoin("/tmp/", ft_itoa(get_random_int()));
	fd[0] = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd[1] = open(filepath, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1)
	{
		node->fd_statuts = 1;
		perror(start->content);
		return (start->next);
	}
	unlink(filepath);
	handle_heredoc(shell, start->content, fd[0]);
	if (fd[1] > 0)
	{
		close(node->in);
		node->in = fd[1];
	}
	return (start->next);
}

void	ft_edit_redirections(t_cmd *head)
{
	t_cmd *current;
	
	current = head;
	while (current) 
	{
		if (current == head && current->in == -1337)
		{
			current->in = open("/dev/stdin", O_RDONLY);
			if (current->in == -1)
				perror("open");
		} 
		if (!current->next && current->out == -1337) 
		{
			current->out = open("/dev/stdout", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (current->out == -1)
				perror("open");
		}
		current = current->next;
	}
}

t_cmd	*ft_cmd(t_shell *shell, t_token **token, t_cmd **cmd_list, t_env *env)
{
	t_token	*tmp;
	t_cmd	*head;
	t_cmd	*cmd_tmp;

	remove_empty_tokens(token);
	tmp = *token;
	cmd_tmp = ft_lstnew_cmd();
	head = cmd_tmp;
	ft_lstadd_back_cmd(cmd_list, cmd_tmp);
	while (tmp)
	{
		tmp = store_cmd_node(shell, cmd_tmp, tmp);
		if (tmp && tmp->type == PIPE)
		{
			cmd_tmp = ft_lstnew_cmd();
			ft_lstadd_back_cmd(cmd_list, cmd_tmp);
			tmp = tmp->next;
		}
	}
	ft_edit_redirections(head);
	return (head);
}

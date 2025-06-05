/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/05 17:36:40 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_redir_in(t_cmd *node, t_token *start)
{
	int	fd;
// printf("int\n");
// exit(0);
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

	// printf("///////////\n");
	// printf("[%s]\n", start->content);
	start = start->next;
	// printf("[%s]\n", start->content);
	if (!start ||!start->content[0])
	{
		// exit(0);
		node->out = -1;
		node->fd_statuts = 1;
		write(2, "ambiguous redirect\n", 19);
		return(start);
	}

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

static	int	len_n(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static t_token	*store_cmd_node(t_shell *shell, t_cmd *node_to_fill, t_token *start)
{
	t_token *tmp;
	if (!start)
		return (NULL);
	
	int fd;
	while (start && start->type != PIPE)
	{
		if (start->type == WORD || start->type == SI_QUOTE)
		{
			node_to_fill->cmd = ft_strjoin2d(node_to_fill->cmd, start->content);
			start = start->next;
		}
		else if (start && start->type == REDIR_IN)
		{
			start = handle_redir_in(node_to_fill, start);
		}
		else if (start && start->type == REDIR_OUT)
		{
			start = handle_redir_out(node_to_fill, start);

			if (!start || !start->content)
				return(start);
		}
		else if (start && start->type == APPEND)
			start = handle_redir_append(node_to_fill, start);
		else if (start && start->type == HEREDOC)
		{
			start = start->next;
			if (!start || !start->content || start->content[0] == '\0')
				start = new_token(ft_strdup(""), HEREDOC);
			// fd = open(handle_heredoc(shell, start->content), O_RDONLY);
			fd = handle_heredoc(shell, start->content);
			if (fd > 0)
			{
				close(node_to_fill->in);
				node_to_fill->in = fd;
			}
			else
				return (NULL);
			start = start->next;
		}
		if (node_to_fill->fd_statuts )
		{
			while (start && start->type != PIPE)
				start = start->next;
			
		}

	}
	return (start);
}


static void remove_empty_tokens(t_token **head)
{
	t_token *curr;
	t_token *prev;
	t_token *tmp;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (!curr->content || curr->content[0] == '\0')
		{
			tmp = curr;
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			curr = curr->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
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

	// remove_empty_tokens(token);
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
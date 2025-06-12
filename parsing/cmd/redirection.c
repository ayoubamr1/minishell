/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:06:13 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/12 17:31:41 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*handle_redir_in(t_cmd *node, t_token *start)
{
	int	fd;
	start = start->next;
	if (start->content && ft_strchr(start->content, ' '))
	{
		node->in = -1;
		node->fd_statuts = 1;
		write(2, "ambiguous redirect\n", 19);
		return(start)->next;
	}
	fd = open(start->content, O_RDONLY);
	if (fd == -1)
	{
		node->fd_statuts = 1;
		perror(start->content);
		return (start->next);
	}
	node->file = ft_strdup(start->content);
	close(node->in);
	node->in = fd;
	return (start->next);
}

t_token	*handle_redir_out(t_cmd *node, t_token *start)
{
	int	fd;
	start = start->next;
	if (!start ||!start->content[0] || (start->content && !ft_strchr(start->content, ' ')))
	{
		node->out = -1;
		node->fd_statuts = 1;
		write(2, "ambiguous redirect\n", 19);
		return(start)->next;
	}
	fd = open(start->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		node->fd_statuts = 1;
		perror(start->content);
		return (start->next);
	}
	node->file = ft_strdup(start->content);
	close(node->out);
	node->out = fd;
	return (start->next);
}

t_token	*handle_redir_append(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		node->fd_statuts = 1;
		perror(start->content);
		return (start->next);
	}
	node->file = ft_strdup(start->content);
	close(node->out);
	node->out = fd;
	return (start->next);
}

void remove_empty_tokens(t_token **head)
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

void	ft_skipe_delimiter(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			tmp->next->type = DILIMITER;
		tmp = tmp->next;
	}
	
}

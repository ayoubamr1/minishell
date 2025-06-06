/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:06:13 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/06 09:07:46 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*handle_redir_in(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
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
	if (!start ||!start->content[0])
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

int get_random_int(void)
{
	int fd = open("/dev/urandom", O_RDONLY);
	unsigned int num = 0;

	if (fd < 0)
		return -1;
	read(fd, &num, sizeof(num));
	close(fd);
	return ((int)(num % 100));
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

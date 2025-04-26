/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/26 17:10:00 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd *ft_lstnew(void)
{
	t_cmd *node = ft_malloc(sizeof(t_cmd), MALLOC);
	if (!node)
		return NULL;
	node->args = NULL;
	node->file = NULL;
	// node->outfile = NULL;
	node->in = -1;
	node->out = -1;
	// node->append = 0;
	// node->heredoc = 0;
	node->next = NULL;
	return node;
}

// static int	ft_lstsize(t_cmd *lst)
// {
// 	int		count;
// 	t_cmd	*sin;

// 	sin = lst;
// 	count = 0;
// 	while (sin)
// 	{
// 		sin = sin->next;
// 		count++;
// 	}
// 	return (count);
// }

// static void	ft_lstclear(t_cmd **lst)
// {
// 	t_cmd	*n;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		n = (*lst)->next;
// 		free((*lst)->args);
// 		free(*lst);
// 		*lst = n;
// 	}
// 	*lst = NULL;
// }

static t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

static void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*final;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	final = ft_lstlast(*lst);
	final->next = new;
	return ;
}

static size_t	ft_count_2d(char **arr)
{
	size_t	i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_strjoin2d(char **s1, char *s2)
{
	size_t	len1;
	size_t	i;
	size_t	j;
	char	**new;

	len1 = ft_count_2d(s1);
	i = 0;
	j = 0;
	if (!s1 && s2)
		return (new = ft_malloc(2 * sizeof(char *), MALLOC), new[0] = ft_strdup(s2), new[1] = NULL, new); 
	if (s1 && !s2)
		return (s1);
	new = ft_malloc(sizeof(char *) * (len1 + 2), MALLOC);
	while (i < len1)
	{
		new[i] = ft_strdup(s1[i]);
		i++;
	}
	new[i++] = ft_strdup(s2);
	new[i] = NULL;
	(free2d (s1), free(s2), s2 = NULL);
	return (new);
}

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

static t_token	*store_cmd_node(t_cmd *node_to_fill, t_token *start)
{
	int	fd;
	
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
		{
			start = start->next;
			fd = open(start->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
				perror(start->content);
			node_to_fill->file = ft_strdup(start->content);
			close(node_to_fill->in);
			(node_to_fill->out = fd, start = start->next);
		}
	}
	return (start);
}

t_cmd	*ft_cmd(t_token **token, t_cmd **cmd_list)
{
	t_token	*tmp;
	t_cmd	*head;
	t_cmd	*cmd_tmp;

	tmp = *token;
	cmd_tmp = ft_lstnew();
	head = cmd_tmp;
	ft_lstadd_back(cmd_list, cmd_tmp);
	while (tmp)
	{
		tmp = store_cmd_node(cmd_tmp, tmp);
		if (tmp && tmp->type == PIPE)
		{
			cmd_tmp = ft_lstnew();
			ft_lstadd_back(cmd_list, cmd_tmp);
			tmp = tmp->next;
		}
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:31:55 by nbougrin          #+#    #+#             */
/*   Updated: 2025/05/10 18:18:34 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd *ft_lstnew_cmd(void)
{
	t_cmd *node = ft_malloc(sizeof(t_cmd), MALLOC);
	if (!node)
		return NULL;
	node->cmd = NULL;
	node->file = NULL;
	// node->outfile = NULL;
	node->in = -1;
	node->out = -1;
	// node->append = 0;
	// node->heredoc = 0;
	node->next = NULL;
	return node;
}

// int	ft_lstsize_cmd(t_cmd *lst)
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

// void	clear_cmd(t_cmd **lst)
// {
// 	t_cmd	*n;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		n = (*lst)->next;
// 		free2d((*lst)->cmd);
// 		(*lst)->cmd = NULL;
// 		free((*lst));
// 		*lst = NULL;
// 		*lst = n;
// 	}
// 	*lst = NULL;
// }
void	clear_cmd(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->cmd)
			free2d(current->cmd);
		if (current->file)
			free(current->file), current->file = NULL;
		free(current);
		current = NULL;
		current = next;
	}
	*lst = NULL;
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*final;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	final = ft_lstlast_cmd(*lst);
	final->next = new;
	return ;
}

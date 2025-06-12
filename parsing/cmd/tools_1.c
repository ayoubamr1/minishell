/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:31:55 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/12 17:39:48 by nbougrin         ###   ########.fr       */
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
	node->in = -1337;
	node->out = -1337;
	node->fd_statuts = -1337;
	node->heredoc_statuts = -1337;
	
	// node->append = 0;
	// node->heredoc = -1;
	node->next = NULL;
	return node;
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
int get_random_int(void)
{
	int				fd;
	unsigned int	num;

	fd = open("/dev/urandom", O_RDONLY);
	num = 0;
	if (fd < 0)
		return -1;
	read(fd, &num, sizeof(num));
	close(fd);
	return ((int)(num % 100));
}

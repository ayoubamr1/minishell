/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:51 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/27 10:13:03 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*new_node(void	*ptr)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

t_list	*last_node(t_list **head)
{
	t_list	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_list	**head, t_list *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
		last_node(head)->next = new;
}

void	clear_all(t_list **head)
{
	t_list	*cur;
	t_list	*tmp;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->ptr);
		cur->ptr = NULL;
		free(cur);
		cur = tmp;
	}
	*head = NULL;
}
static void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_malloc(size_t size, t_call call)
{
	static t_list	*head;
	t_list			*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
			(clear_all(&head), exit(1));
		tmp = new_node(ptr);
		if (!tmp)
			(clear_all(&head), free(ptr), exit(1));
		add_back(&head, tmp);
		ft_bzero(ptr, size);
		return (ptr);
	}
	else if (call == FREE)
		clear_all(&head);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:51 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/26 21:24:21 by nbougrin         ###   ########.fr       */
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

// void	clear_all(t_list **head)
// {
// 	t_list	*cur;
// 	t_list	*tmp;

// 	if (!head || !*head)
// 		return ;
// 	cur = *head;
// 	while (cur)
// 	{
// 		tmp = cur->next;
// 		free(cur->ptr);
// 		cur->ptr = NULL;
// 		free(cur);
// 		cur = tmp;
// 	}
// 	*head = NULL;
// }

void clear_all(t_list **head)
{
    t_list *cur;
    t_list *tmp;

    if (!head)
        return;
    
    cur = *head;
    while (cur) {
        tmp = cur->next;
        if (cur->ptr) {
            free(cur->ptr);
            cur->ptr = NULL;  // Mark as freed
        }
        free(cur);
        cur = tmp;
    }
    *head = NULL;  // Ensure the caller's pointer is set to NULL
    head = NULL;  // Ensure the caller's pointer is set to NULL
}
static void check_list_integrity(t_list *head)
{
    t_list *current = head;
    t_list *runner;
    
    while (current)
    {
        // Check for duplicates
        runner = head;
        while (runner != current)
        {
            if (runner->ptr == current->ptr)
                printf("Warning: Duplicate pointer found in list: %p\n", runner->ptr);
            runner = runner->next;
        }
        current = current->next;
    }
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
	{
		check_list_integrity(head);
		clear_all(&head);
	}
	return (NULL);
}

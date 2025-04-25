#include "../../minishell.h"

t_cmd	*ft_lstnew()
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	// node->args = ;
	node->next = NULL;
	return (node);
}


int	ft_lstsize(t_cmd *lst)
{
	int		count;
	t_cmd	*sin;

	sin = lst;
	count = 0;
	while (sin)
	{
		sin = sin->next;
		count++;
	}
	return (count);
}

void	ft_lstclear(t_cmd **lst)
{
	t_cmd	*n;

	if (!lst)
		return ;
	while (*lst)
	{
		n = (*lst)->next;
		free((*lst)->args);
		free(*lst);
		*lst = n;
	}
	*lst = NULL;
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
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

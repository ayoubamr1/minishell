#include "../../minishell.h"

static t_env	*ft_lstnew_env(char *content)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env), MALLOC);
	node->content = content;
	node->next = NULL;
	return (node);
}

// static int	ft_lstsize(t_env *lst)
// {
// 	int		count;
// 	t_env	*sin;

// 	sin = lst;
// 	count = 0;
// 	while (sin)
// 	{
// 		sin = sin->next;
// 		count++;
// 	}
// 	return (count);
// }

// static void	clear_env(t_env **lst)
// {
// 	t_env	*n;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		n = (*lst)->next;
// 		free((*lst)->content);
// 		((*lst)->content) = NULL;
// 		free(*lst);
// 		*lst = n;
// 	}
// 	*lst = NULL;
// }

// static t_env	*ft_lstlast(t_env *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// static void	ft_lstadd_back(t_env **lst, t_env *new)
// {
// 	t_env	*final;

// 	if (!new || !lst)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	final = ft_lstlast(*lst);
// 	final->next = new;
// 	return ;
// }

t_env *ft_env(t_env *env_list, char **env)
{
	t_env *tmp;
	int i;

	i = 0;
	env_list = ft_lstnew_env(ft_strdup(env[i++]));
	tmp = env_list;
	while (env[i])
	{
		tmp->next = ft_lstnew_env(ft_strdup(env[i]));;
		tmp = tmp->next;
		i++;
	}
	return (env_list);
}

#include "../../minishell.h"

static t_env	*ft_lstnew_env(char *content)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env), MALLOC);
	node->content = content;
	node->flag = 0;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*final;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		// printf("lst befor\n");
		// print_env_list(*lst);
		*lst = new;
		// printf("lst after\n");
		// print_env_list(*lst);
		return ;
	}
	final = ft_lstlast(*lst);
	final->next = new;
	return ;
}

// void print_env_list(t_env *lst)
// {
// 	while (lst)
// 	{
// 		printf("lst = %s\n", lst->content);
// 		lst = lst->next;
// 	}
// }

static t_env *ft_hard_env()
{
	t_env *env;
	t_env *tmp;

	env = ft_lstnew_env(ft_strdup("PWD=/home/nbougrin/pull"));
	tmp = env;
	tmp->next = ft_lstnew_env(ft_strdup("PATH=/home/nbougrin/bin:\
				/home/nbougrin/bin:/home/nbougrin/bin:/usr/local/sbin:\
				/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:\
				/usr/local/games:/snap/bin"));
	tmp->next->next = ft_lstnew_env(ft_strdup("SHLVL=1"));
	tmp->next->next->next = ft_lstnew_env(ft_strdup("_=/usr/bin/env"));
	return(env);
}
t_env *ft_env(t_env *env_list, char **env)
{
	t_env *tmp;
	int i;

	i = 0;
	if (env && *env)
	{

		env_list = ft_lstnew_env(ft_strdup(env[i++]));
		tmp = env_list;
		while (env[i])
		{
			tmp->next = ft_lstnew_env(ft_strdup(env[i]));;
			tmp = tmp->next;
			i++;
		}
	}
	else 
		return (ft_hard_env());
	return (env_list);
}

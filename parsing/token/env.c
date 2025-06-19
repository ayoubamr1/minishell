/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:07:36 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/19 21:30:36 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_env	*ft_lstnew_env(char *content)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env), MALLOC);
	node->content = content;
	node->flag = 0;
	node->quot = 0;
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

static	char	*ft_new(void)
{
	char	*s1;
	char	*s2;
	char	*g1;

	s1 = ft_strdup("PATH=/home/nbougrin/bin:");
	s2 = ft_strdup("/home/nbougrin/bin:/home/nbougrin/bin:/usr/local/sbin:");
	g1 = ft_strjoin(s1, s2);
	return (g1);
}

static t_env	*ft_hard_env(void)
{
	t_env	*env;
	t_env	*tmp;
	char	*s3;
	char	*s4;
	char	*path;

	s3 = ft_strdup("/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:");
	s4 = ft_strdup("/usr/local/games:/snap/bin");
	path = ft_strjoin(s3, s4);
	env = ft_lstnew_env(getcwd(NULL, 0));
	tmp = env;
	tmp->next = ft_lstnew_env(ft_strjoin(ft_new(), path));
	tmp->next->next = ft_lstnew_env(ft_strdup("SHLVL=1"));
	return (env);
}

t_env	*ft_env(t_env *env_list, char **env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (env && *env)
	{
		env_list = ft_lstnew_env(ft_strdup(env[i++]));
		tmp = env_list;
		while (env[i])
		{
			tmp->next = ft_lstnew_env(ft_strdup(env[i]));
			tmp = tmp->next;
			i++;
		}
	}
	else
		return (ft_hard_env());
	return (env_list);
}

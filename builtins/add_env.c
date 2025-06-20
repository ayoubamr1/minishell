/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:38:40 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/19 20:28:18 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_env(t_shell *main, char *new_var)
{
	t_env	*new_node;
	t_env	*cur;

	new_node = ft_malloc(sizeof(t_env), MALLOC);
	new_node->content = ft_strdup(new_var);
	new_node->next = NULL;
	cur = main->env;
	if (!cur)
		main->env = new_node;
	else
	{
		while (cur)
		{
			if (!ft_strcmp(cur->content, new_var))
			{
				cur->content = new_node->content;
				return ;
			}
			cur = cur->next;
		}
		ft_lstadd_back_env(&main->env, new_node);
	}
}

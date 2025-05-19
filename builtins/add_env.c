/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:38:40 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/19 11:38:07 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_env(t_shell *main, char *new_var)
{
	t_env	*new_node;
	t_env	*cur;
	
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(new_var);
	new_node->next = NULL;
	// printf("new_nod = %s\n", new_node->content);
	cur = main->env;
	if (!cur)            // if the linked liste is empty , so we add it in the first node
		main->env = new_node;
	else
	{
		while (cur)
		{
			// printf("%s\n", cur->content);
			cur = cur->next;
		}
		// cur->next = new_node;
		// return ;
		ft_lstadd_back_env(&main->env, new_node); // we add it at the end
	}
	// add_to_env(main, new_var); // if not found add it in the environment variable
}

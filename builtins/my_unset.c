/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:06:40 by ayameur           #+#    #+#             */
/*   Updated: 2025/04/30 17:37:13 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env(t_shell *main, char *var_name)
{
	t_env	*cur;
	t_env	*prev;
	size_t	len;

	prev = NULL;
	len = ft_strlen(var_name);
	cur = main->env;
	while (cur)
	{
		if (ft_strncmp(cur->content, var_name, len) == 0 && cur->content[len + 1] == '=')
		{
			if (prev)                // case where prev != NULL
				prev->next = cur->next;
			else					 // case where we we want to remove the first node
				main->env = cur->next;
			free(cur->content);
			free(cur);
			return ;
		}
		prev = cur;                  // update prev
		cur = cur->next;
	}
}
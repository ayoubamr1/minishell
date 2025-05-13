/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:48:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/13 19:09:27 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_env *env, char *var_updated)
{
	char	*pos_equal;
	t_env	*cur;
	size_t	len;
	
	pos_equal = ft_strchr(var_updated, '=');
	if (!pos_equal)
		return ;
	len = pos_equal - var_updated;
	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->content, var_updated, len) == 0 && cur->content[len + 1] == '=')
		{
			free(cur->content);
			cur->content = ft_strdup(var_updated);
			return ;	
		}
		cur = cur->next;
	}
	add_env(cur, var_updated);
}

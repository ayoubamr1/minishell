/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:48:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/14 19:21:53 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_shell *main, char *var_updated)
{
	char	*pos_equal;
	t_env	*cur;
	size_t	len;
	
	// printf("====== hna =======\n");
	pos_equal = ft_strchr(var_updated, '=');
	if (!pos_equal)
		return ;
	len = pos_equal - var_updated;
	cur = main->env;
	while (cur)
	{
		if (ft_strncmp(cur->content, var_updated, len) == 0 && cur->content[len + 1] == '=')
		{
			free(cur->content);
			cur->content = ft_strdup(var_updated);
			printf("%s\n", cur->content);
			return ;	
		}
		cur = cur->next;
	}
	add_to_env(main, var_updated);
}

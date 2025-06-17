/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:06:40 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/14 18:08:31 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_env(t_shell *main, char **var_name)
{
	t_env	*cur;
	t_env	*prev;
	size_t	var_len;
	char	*equal_signel;
	int		i;

	i = 0;
	while (var_name[i])
	{
		cur = main->env;
		prev = NULL;
		var_len = ft_strlen(var_name[i]);
		while (cur)
		{
			if (ft_strncmp(cur->content, var_name[i], var_len) == 0 
				&& cur->content[var_len] == '=')
			{
				if (prev)                // case where prev != NULL
					prev->next = cur->next;
				else					 // case where we we want to remove the first node
					main->env = cur->next;
				free(cur->content);
				free(cur);
				break ;
			}
			prev = cur;                  // update prev
			cur = cur->next;
		}
		i++;
	}
	return (1);
}

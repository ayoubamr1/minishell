/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:50:07 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/14 12:35:20 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv( t_shell *main, char *var_name) // t_shell *main
{
	size_t	len;
	t_env	*tmp;
	
	len = ft_strlen(var_name);
	tmp = main->env;
	// if (!tmp)
	// {
	// 	printf("main->env is NULL!\n");
    // 	return NULL;
	// }
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var_name, len) == 0 && tmp->content[len] == '=')
			return (tmp->content + len + 1);
		tmp = tmp->next;
		// i++;
	}
	return (NULL);
}

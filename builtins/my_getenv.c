/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:50:07 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/02 14:57:04 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char **env, char *var_name) // t_shell *main
{
	size_t	len;
	t_env	*tmp;
	int		i;
	
	len = ft_strlen(var_name);
	i = 0;
	// // tmp = main->env;
	// if (!tmp)
	// {
	// 	printf("main->env is NULL!\n");
    // 	return NULL;
	// }
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[len + 1]);
		// tmp = tmp->next;
		i++;
	}
	return (NULL);
}

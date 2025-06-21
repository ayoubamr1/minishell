/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/20 19:43:38 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_shell *main)
{
	t_env *env;
	
	env = main->env;
	while (env)
	{
		if (ft_strchr(env->content, '='))
			printf("%s\n", env->content);
		env = env->next;
	}
	return (0);
}

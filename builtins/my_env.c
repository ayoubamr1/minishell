/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/05 14:17:40 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(t_shell *main)
{
	t_env *env = main->env;
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
	return (0);
}

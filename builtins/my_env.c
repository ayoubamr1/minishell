/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:57:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/19 18:58:17 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env(t_shell *main)
{
	t_env *env = main->env;
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

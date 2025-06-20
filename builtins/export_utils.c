/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:50 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/19 20:36:12 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**copy_env_to_array(t_env *env, int count)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_malloc(sizeof(char *) * (count + 1), MALLOC);
	while (env)
	{
		array[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

void	printf_env_array(char **array)
{
	int	i;
	int	equal_pos;

	i = 0;
	while (array[i])
	{
		equal_pos = search_equal(array, i);
		write (1, "declare -x ", 11);
		if (equal_pos != -1)
		{
			write (1, array[i], equal_pos + 1);
			write (1, "\"", 1);
			write (1, array[i] + equal_pos + 1, ft_strlen(array[i] + equal_pos + 1));
			write (1, "\"\n", 2);
		}
		else
		{	
			printf("%s\n", array[i]);
		}
		i++;
	}
}

void	environment(t_env *env)
{
	int		count;
	char	**array;

	count = count_env(env);
	array = copy_env_to_array(env, count);
	array = arrange_array(array);
	printf_env_array(array);
}

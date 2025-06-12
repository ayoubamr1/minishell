/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:01:30 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/11 16:07:17 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_flag_true(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	my_echo(char **av, t_cmd *cur)
{
	// char **av = cur->cmd;
	// printf("==============\n");
	// printf("%s\n", av[1]);
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (if_flag_true(av[i]))
	{
		flag = 1;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");	
	return (0);
}

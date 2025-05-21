/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:01:30 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/20 13:05:29 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_echo(char **av, t_cmd *cur)
{
	// char **av = cur->cmd;
	// printf("==============\n");
	// printf("%s\n", av[1]);
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			write(1, &av[i][j], 1);
			j++;
		}
		if (av[i + 1])
			write (1, " ", 1);
		i++;
	}
	write (1, "\n", 1);
	return (0);
}

// int main (int ac , char **av)
// {
// 	(void)ac;
// 	echo(av);
// }
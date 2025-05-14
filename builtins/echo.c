/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:01:30 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/14 20:10:44 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_cmd *cur)
{
	char **av = cur->cmd;
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			write(cur->out, &av[i][j], 1);
			j++;
		}
		if (av[i + 1])
			write (cur->out, " ", 1);
		i++;
	}
	return (0);
}

// int main (int ac , char **av)
// {
// 	(void)ac;
// 	echo(av);
// }
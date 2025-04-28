/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/04/23 11:29:16 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export(char **av)
{
	char	**name;
	char	*value;
	
	
	if (av[1] == NULL)
	{
		fprintf(stderr, "missigne argument"); // need to change
		return (1);
	}
	name = ft_split(av[1], '=');
	if (name == NULL || name[0] == NULL || name[1] == NULL)
	{
		fprintf(stderr, "export : invalid format"); // need to change 
		return (1);
	}
	// need to update in my enviroment variable
	
}
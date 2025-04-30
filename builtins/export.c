/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/04/30 16:45:12 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(char	*input, t_shell *main_struct)
{
	char	var_name[100];
	char	*value;
	int 	i;
	int		j;
	
	j = 0;
	while (input[j])
	{
		if (input[j] == '$')
		{	
			j++;
			i = 0;
			while (input[j] && (ft_isalnum(input[j]) || input[j] == '_' ))
				var_name[i++] = input[j++];
			var_name[i] = '\0';
			value = my_getenv(main_struct, var_name);
			if (value)
				printf("%s", value);
		}
		else
		{
			ft_putchar(input[j]);
			j++;
		}
	}
	printf("\n");
	// if (av[1] == NULL)
	// {
	// 	fprintf(stderr, "missigne argument"); // need to change
	// 	return (NULL);
	// }
	// name = ft_split(av[1], '='); // if we need to export a lot of variable int the same commande line, 
	// 							 //	we need to creat a 3D array
	// 							 // and allocate for each 2D array that return split inside 
	// 							 // 3D array
	// if (name == NULL || name[0] == NULL || name[1] == NULL)
	// {
	// 	fprintf(stderr, "export : invalid format"); // need to change 
	// 	return (NULL);
	// }
	// return (name);
	// // need to update in my enviroment variable
}

int main ()
{
	// (void)ac;
	// export("hello $USER, you home is $HOME");
	// export("$USER $HOME");
	// int i = 0;
	// while (s[i])
	// {
	// 	printf("[%s][%p]\n", s[i], &s[i]);
	// 	i++;
	// }
}
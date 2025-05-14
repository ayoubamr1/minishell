/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:30:43 by ayameur           #+#    #+#             */
/*   Updated: 2025/05/14 15:42:12 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_export(t_shell *main, char *var)
{
	t_env	*curr;
	size_t	len;
	char	*new_var;
	char	*signe_equal;
	char	buffer[256];
	char	*value;
	int		i;
	
	i = 0;
	signe_equal = ft_strchr(var, '=');
	len = signe_equal - var;
	ft_strncpy(buffer, var, len);
	buffer[len] = '\0';
	value = signe_equal + 1;
	curr = main->env;
	new_var = malloc(ft_strlen(var) + 1);
	if (!new_var)
		return;
	ft_strcpy(var, new_var);
	while (curr)
	{
		if (ft_strncmp(curr->content, var, len) == 0 && curr->content[len] == '=')
		{
			free(curr->content);
			curr->content = new_var;
			return ;
		}
		curr = curr->next;
	}
	add_to_env(main, new_var);
}






















// void	export(char	*input, char **env)//t_shell *main_struct)
// {
// 	char	var_name[100];
// 	char	*value;
// 	int 	i;
// 	int		j;
	
// 	j = 0;
// 	while (input[j])
// 	{
// 		if (input[j] == '$')
// 		{	
// 			j++;
// 			i = 0;
// 			while (input[j] && (ft_isalnum(input[j]) || input[j] == '_' ))
// 				var_name[i++] = input[j++];
// 			var_name[i] = '\0';
// 			value = my_getenv(env, var_name); // main_struct
// 			if (value)
// 				printf("%s", value);
// 		}
// 		else
// 		{
// 			ft_putchar(input[j]);
// 			j++;
// 		}
// 	}
// 	printf("\n");
// 	// if (av[1] == NULL)
// 	// {
// 	// 	fprintf(stderr, "missigne argument"); // need to change
// 	// 	return (NULL);
// 	// }
// 	// name = ft_split(av[1], '='); // if we need to export a lot of variable int the same commande line, 
// 	// 							 //	we need to creat a 3D array
// 	// 							 // and allocate for each 2D array that return split inside 
// 	// 							 // 3D array
// 	// if (name == NULL || name[0] == NULL || name[1] == NULL)
// 	// {
// 	// 	fprintf(stderr, "export : invalid format"); // need to change 
// 	// 	return (NULL);
// 	// }
// 	// return (name);
// 	// // need to update in my enviroment variable
// }

// int main (int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	// t_shell *env = NULL;
// 	// (void)ac;
// 	// export("hello $USER, you home is $HOME");
// 	export("somethis=ayoub", env);
// 	// int i = 0;
// 	// while (s[i])
// 	// {
// 	// 	printf("[%s][%p]\n", s[i], &s[i]);
// 	// 	i++;
// 	// }
// }
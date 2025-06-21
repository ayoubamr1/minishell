/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:58:16 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/21 11:17:00 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_pwd(t_shell *main)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = my_getenv(main, "PWD");
		if (!pwd)
			return (1);
		printf("%s\n", pwd);
		return (0);
	}	
	printf("%s\n", pwd);
	free (pwd);
	return (0);
}

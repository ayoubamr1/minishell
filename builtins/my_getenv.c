/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:50:07 by ayameur           #+#    #+#             */
/*   Updated: 2025/04/30 16:32:46 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(t_shell *main, char *var_name)
{
	int		i;
	size_t	len;
	t_env	*tmp;
	
	len = ft_strlen(var_name);
	i = 0;
	tmp = main->env;
	while (tmp)
	{
		if (ft_strncmp(tmp, var_name, len) == 0 && tmp->content[len + 1] == '=')
			return (tmp->content + len + 2);
		tmp = tmp->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:17:27 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 16:26:39 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free2d(char **str)
{
	int i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return ;
}

// int	ft_isalnum(int c)
// {
// 	if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
// 		|| (c >= 48 && c <= 57))
// 		return (1);
// 	return (0);
// }
// int	ft_isalpha(int c)
// {
// 	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
// 		return (1);
// 	return (0);
// }

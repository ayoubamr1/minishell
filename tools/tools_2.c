/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:17:27 by nbougrin          #+#    #+#             */
/*   Updated: 2025/05/12 19:04:54 by ayameur          ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	char	tp;
	int		i;

	i = 0;
	tp = (char) c;
	while (s[i])
	{
		if (s[i] == tp)
			return ((char *) &s[i]);
		else
			i++;
	}
	if (s[i] == tp)
		return ((char *) &s[i]);
	return (NULL);
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

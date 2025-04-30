/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:17:27 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/30 17:52:51 by ayameur          ###   ########.fr       */
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

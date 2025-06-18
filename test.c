/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:10:14 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/18 16:15:16 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_space(char *str)
{
	char	**new;
	char	quote;
	int		start;
	int		i;

	(1) && (quote = 0, new = NULL, i = 0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		start = i;
		while (str[i] && str[i] != ' ')
		{
			if (ft_quote(str[i]))
			{
				quote = str[i++];
				while (str[i] && str[i] != quote)
					i++;
			}
			i++;
		}
		new = ft_strjoin2d(new, remove_quotes(substr(str, start, i - start)));
	}
	return (new);
}

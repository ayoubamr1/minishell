/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:13:18 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 18:45:28 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_numlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*id_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

// char	*remove_quotes(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	quote;
// 	char	*res;

// 	(1) && (i = 0, j = 0);
// 	quote = 0;
// 	res = malloc(strlen(str) + 1);
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if ((str[i] == '\'' || str[i] == '"'))
// 		{
// 			if (quote == 0)
// 				quote = str[i];
// 			else if (quote == str[i])
// 				quote = 0;
// 			i++;
// 		}
// 		else
// 			res[j++] = str[i++];
// 	}
// 	res[j] = '\0';
// 	return (res);
// }
static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'' || c == ' ');
}
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;
	(1) && (i = 0, j = 0);
	quote = 0;
	res = ft_malloc(strlen(str) + 1, MALLOC);
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '\'' && str[i] != '"')
		res[j++] = str[i++];
	if (str[i] && (str[i] == '\'' || str[i] == '"'))
		quote = str[i++];
	else
	{
		res[j] = '\0';
		return (res);
	}
	while (str[i] && str[i] != quote)
		res[j++] = str[i++];
	i++;
	while (str[i] && !is_special_char(str[i]))
		res[j++] = str[i++];
	res[j] = '\0';
	return (res);
}

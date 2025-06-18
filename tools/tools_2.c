/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:17:27 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/18 18:42:04 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	tp;
	int		i;

	i = 0;
	tp = (char) c;
	if (!s)
		return (NULL);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	**env_in_2D(t_shell *main)
{
	t_env	*cur;
	int		count;
	char	**env;
	
	cur = main->env;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;		
	}
	env = (char **)ft_malloc(sizeof(char *) * (count + 1), MALLOC);
	count = 0;
	cur = main->env;
	while (cur)
	{
		env[count] = cur->content;
		count++;
		cur = cur->next;
	}
	env[count] = NULL;
	return (env);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long int	check;
	unsigned long		res;

	i = 0;
	signe = 1;
	res = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' ')))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = res;
		res = res * 10 + str[i++] - 48;
		if (res < check)
		{
			if (signe == -1)
				return (0);
			return (-1);
		}
	}
	return (res * signe);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

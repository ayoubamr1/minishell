/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:06:29 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/12 16:50:20 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_word(const char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			cnt++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (cnt);
}

void	ft_free(char	**s, int indice)
{
	int	i;

	i = 0;
	while (i < indice)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	*ft_strndup(const char *str, unsigned int n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	ptr = ft_malloc((n + 1), MALLOC);
	if (!ptr)
		return (NULL);
	while (n--)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	get_current_word(const char *str, int c, int *i, int *start)
{
	if (i == NULL || start == NULL)
		return ;
	while (str[*i] && str[*i] == c)
		*(i) = *(i) + 1;
	*start = *i;
	while (str[*i] && str[*i] != c)
		*(i) = *(i) + 1;
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		word;
	int		start;
	char	**s;

	i = 0;
	word = 0;
	start = 0;
	s = ft_malloc((sizeof(char *)) * (ft_count_word(str, c) + 1), MALLOC);
	if (!s)
		return (NULL);
	while (str[i])
	{
		get_current_word(str, c, &i, &start);
		if (i > start)
		{
			s[word] = ft_strndup(str + start, i - start);
			if (!s[word])
				return (ft_free(s, word), NULL);
			word++;
		}
	}
	s[word] = NULL;
	return (s);
}

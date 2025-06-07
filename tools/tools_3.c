/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:06:29 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/07 18:34:04 by nbougrin         ###   ########.fr       */
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
	ptr = malloc(n + 1);
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
	s = malloc ((sizeof(char *)) * (ft_count_word(str, c) + 1));
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

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

int ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
    	return 1;
	return 0;
}

size_t	ft_count_2d(char **arr)
{
	size_t	i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_strjoin2d(char **s1, char *s2)
{
	size_t	len1;
	size_t	i;
	char	**new;

	len1 = ft_count_2d(s1);
	i = 0;
	if (!s1 && s2)
		return (new = ft_malloc(2 * sizeof(char *), MALLOC), new[0] = ft_strdup(s2), new[1] = NULL, new); 
	if (s1 && !s2)
		return (s1);
	new = ft_malloc(sizeof(char *) * (len1 + 2), MALLOC);
	while (i < len1)
	{
		new[i] = ft_strdup(s1[i]);
		i++;
	}
	new[i++] = ft_strdup(s2);
	new[i] = NULL;
	return (new);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

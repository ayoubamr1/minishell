/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:47:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/09 21:13:13 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *new_token(char *content, t_token_type type)
{
    t_token *tok = malloc(sizeof(t_token));
    if (!tok)
        return (NULL);
    tok->content = content;
    tok->type = type;
    tok->next = NULL;
    return (tok);
}

void add_token(t_token **lst, char *content, t_token_type type, int index)
{
    t_token *tok = new_token(content, type);
    if (!*lst)
        *lst = tok;
    else
	{
        t_token *tmp = *lst;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = tok;
    }
		tok->index = index;
} 

char *ft_substr(char *s, int start, int len)
{
    char *out = malloc(len + 1);
    if (!out)
        return (NULL);
    strncpy(out, s + start, len);
    out[len] = 0;
    return (out);
}
void qoute(t_token **tokens, int *i, char *input, int *index)
{
	int start;
	char quote;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	add_token(tokens, ft_substr(input, start, *i - start), STRING, *index);
	if (input[*i] == quote)
		(*i)++;
		(*index)++;
}
void	ft_word(t_token **tokens, int *i, char *input, int *index)
{
	int	start;
	start = *i;
	while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '|' &&
			input[(*i)] != '<' && input[(*i)] != '>' &&
			input[(*i)] != '"' && input[(*i)] != '\'')
		(*i)++;
	add_token(tokens, ft_substr(input, start, (*i) - start), WORD, *index);
	(*index)++;
}


// --------------------------


size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}



static	char	*str_cpy(const char *str, char *dest)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	return (str_cpy(s1, dest));
}



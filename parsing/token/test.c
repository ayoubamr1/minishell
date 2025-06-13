#include "../../minishell.h"
#include <stdbool.h>
bool is_quote(char c) 
{
	return c == '\'' || c == '\"';
}

int token_str(t_token **tokens, char *input, int *i, int *index)
{
	int		start;
	bool	in_quote;
	char	quote_char;

	start = *i;
	in_quote = false;
	quote_char = 0;
	while (input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (is_quote(input[*i]))
		{
			if (!in_quote)
			{
				in_quote = true;
				quote_char = input[*i];
			}
			else if (input[*i] == quote_char)
				in_quote = false;
		}
		else if (input[*i] == ' ' && !in_quote)
			break;
		(*i)++;
	}
	if (*i > start)
		add_token(tokens, substr(input, start, (*i) - start), WORD, (*index)++);
	while (input[*i] == ' ' && !in_quote)
		(*i)++;
	return 0;
}


char    *ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t  s_len;
	size_t  i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
			return (ft_strdup(""));
	if (len > s_len - start)
			len = s_len - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

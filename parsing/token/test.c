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
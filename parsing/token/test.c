#include "../../minishell.h"

void *token_str(t_token **token, char *input, int *i, int *index)
{
	char quote; 
	int start;
	int s;
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		s = 1;
		quote = input[*i];
		while (input[*i])
		{
			if (input[*i] == quote)
			{
				s++;
				break;
			}
		}
		while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
			(*i)++;
		
		// add_token(token, substr(), WORD, (*index));
		add_token(token, substr(input, start, (*i) - start), WORD, (*index));
	}
	
}
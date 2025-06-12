/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/12 17:26:08 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int token_str(t_token **tokens, char *input, int *i, int *index)
{
	int start;
	char quote_char;

	start = *i;
	quote_char = 0; 
	while (input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if ((input[*i] == '\'' || input[*i] == '\"'))
		{
			if (quote_char == 0)
				quote_char = input[*i];
			else if (input[*i] == quote_char)
				quote_char = 0;
		}
		else if (input[*i] == ' ' && quote_char == 0)
			break;
		(*i)++;
	}
	if (*i > start)
		add_token(tokens, substr(input, start, (*i) - start), WORD, (*index)++);
	while (input[*i] == ' ' && quote_char == 0)
		(*i)++;
	return 0;
}

void lexer_2(t_token **tokens, char *input, int *i, int *index)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, ft_strdup("<<"), HEREDOC, *index);
		((*i) += 2, (*index)++);
	}
	else if (input[*i] == '>')
	{
		add_token(tokens, ft_strdup(">"), REDIR_OUT, (*index));
		((*i)++, (*index)++);
	}
	else if (input[(*i)] == '|')
	{
		add_token(tokens, ft_strdup("|"), PIPE, (*index));
		((*i)++, (*index)++);
	}
	else if (input[*i] == '<')
	{
		add_token(tokens, ft_strdup("<"), REDIR_IN, (*index));
		((*i)++, index++);
	}
	else if (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
			input[*i] != '<' && input[*i] != '>' ) 
		token_str(tokens, input, i, index);
}

int lexer_1(char *input, t_token **tokens)
{
	int i;
	int index;

	i = 0;
	index = 1;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(tokens, ft_strdup(">>"), APPEND, index);
			(i += 2, index++);
		}
		else
			lexer_2(tokens, input, &i, &index);
	}
	return (1);
}

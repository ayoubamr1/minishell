/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 18:30:57 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_token(t_token **lst)
{
	t_token	*n;

	if (!lst)
		return ;
	while (*lst)
	{
		n = (*lst)->next;
		if ((*lst)->content) // protect double free
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		free(*lst);
		*lst = NULL;
		*lst = n;
	}
}


void *token_str(t_token **token, char *input, int *i, int *index)
{
    char quote;
    int start;
    int found_closing_quote = 0;

    start = *i;

    // Read until we find a quote or operator
    while (input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
        (*i)++;

    if (input[*i] == '"' || input[*i] == '\'')
    {
        quote = input[*i];
        (*i)++;  // skip opening quote

        while (input[*i])
        {
            if (input[*i] == quote)
            {
                found_closing_quote = 1;
                (*i)++;  // skip closing quote
                break;
            }
            (*i)++;
        }

        // if quote not closed
        if (!found_closing_quote)
        {
            printf("Syntax error: unclosed quote\n");
            return NULL;
        }

        // Read after quote until next special char
        while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
            (*i)++;

        char *value = substr(input, start, *i - start);
        if (quote == '"')
            add_token(token, value, WORD, (*index));
        else
            add_token(token, value, SI_QUOTE, (*index));
        (*index)++;
        return NULL;
    }

    char *value = substr(input, start, *i - start);
    add_token(token, value, WORD, (*index));
    (*index)++;
    return NULL;
}

void	ft_word(t_token **tokens, char *input, int *i, int *index)
{
	int start;

	start = (*i);
		while (input[(*i)] && input[(*i)] != ' ' && input[(*i)] != '|' &&
				input[(*i)] != '<' && input[(*i)] != '>' &&
				input[(*i)] != '"' && input[(*i)] != '\'')
			(*i)++;
		add_token(tokens, substr(input, start, (*i) - start), WORD, (*index));
		(*index)++;
}

void lexer_2(t_token **tokens, char *input, int *i, int *index)
{
	// char *word;

	if (input[*i] == '>')
		{
			add_token(tokens, ft_strdup(">"), REDIR_OUT, *index);
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
	else
		ft_word(tokens, input, i, index);
	// else if (input[(*i)] == '"' || input[(*i)] == '\'')
	// {
	// 	if (input[*i] == '\'' || input[*i] == '"')
	// 	{
	// 		word = parse_word_with_quotes(input, i);
	// 		// add_token(tokens, word, STRING, (*index)++);
	// 	}
	// }
}

void lexer_1(char *input, t_token **tokens)
{
	int i;
	int index;


	i = 0;
	index = 1;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] && input[i] != ' ' && input[i] != '|' &&
			input[i] != '<' && input[i] != '>' ) 
		{
			token_str(tokens, input, &i, &index);
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(tokens, ft_strdup(">>"), APPEND, index);
			(i += 2, index++);
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(tokens, ft_strdup("<<"), HEREDOC, index);
			(i += 2, index++);
		}
		else
			lexer_2(tokens, input, &i, &index);
	}
	return ;
}

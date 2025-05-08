/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/05/08 17:23:08 by ayameur          ###   ########.fr       */
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
		if ((*lst)->content)
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		free(*lst);
		*lst = NULL;
		*lst = n;
	}
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'' || c == ' ');
}

static int	skip_quote_block(char *input, int *i, char quote)
{
	while (input[*i])
	{
		if (input[*i] == quote)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

static void	handle_quoted_token(t_token **token, char *input, int *i, int *index, char *str)
{
	int		start;
	char	quote;
	char	*value;
	char	*s1;

	start = *i;
	quote = input[*i];
	(*i)++;
	if (!skip_quote_block(input, i, quote))
	{
		printf("Syntax error: unclosed quote\n");
		return ;
	}
	while (input[*i] && !is_special_char(input[*i]))
		(*i)++;
	
	// while (input[*i] && input[(*i)+ 1] != ' ')
	while (input[*i] && !is_special_char(input[*i]))
	{
		quote = input[*i];
		(*i)++;
		if (!skip_quote_block(input, i, quote))
		{
			printf("Syntax error: unclosed quote\n");
			return ;
		}
		while (input[*i] && !is_special_char(input[*i]))
			(*i)++;
	}
	
	s1 = ft_strjoin(str, substr(input, start, *i - start));
	if (quote == '\'')
	add_token(token, s1, SI_QUOTE, *index);
	else
	add_token(token, s1, WORD, *index);
	(*index)++;
}

void	*token_str(t_token **token, char *input, int *i, int *index)
{
	int		start;
	char	*value;

	start = *i;
	while (input[*i] && !is_special_char(input[*i]))
		(*i)++;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		value = substr(input, start, *i - start);
		handle_quoted_token(token, input, i, index, value);
		return (NULL);
	}
	value = substr(input, start, *i - start);
	add_token(token, value, WORD, *index);
	(*index)++;
	return (NULL);
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
	// 	if (ieenput[*i] == '\'' || input[*i] == '"')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/12 19:27:26 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_special_q(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
}

static int	handle_quoted_token(t_parm *parm, char *input, int *i)
{
	int		start;
	char	quote;

	(1) && (start = *i, quote = input[(*i)++]);
	if (!skip_quote_block(input, i, quote))
	{
		printf("Syntax error: unclosed quote\n");
		return (1);
	}
	while (input[*i] && !is_special_q(input[*i]))
		(*i)++;
	while (input[*i] && !is_special_q(input[*i]))
	{
		quote = input[(*i)++];
		if (!skip_quote_block(input, i, quote))
		{
			printf("Syntax error: unclosed quote\n");
			return (1);
		}
		while (input[*i] && !is_special_q(input[*i]))
			(*i)++;
	}
	parm->s1 = ft_strjoin(parm->str, substr(input, start, *i - start));
	return (0);
}

int	token_str(t_token **token, char *input, int *i, int *index)
{
	int		start;
	char	*value;
	t_parm	*parm;

	parm = ft_malloc(sizeof(t_parm), MALLOC);
	start = *i;
	while (input[*i] && !is_special_char(input[*i]))
		(*i)++;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		parm->str = substr(input, start, *i - start);
		if (handle_quoted_token(parm, input, i))
			return (1);
		else
		{
			if (parm->quote == '\'')
				add_token(token, parm->s1, SI_QUOTE, (*index)++);
			else
				add_token(token, parm->s1, WORD, (*index)++);
		}
		return (0);
	}
	value = substr(input, start, *i - start);
	add_token(token, value, WORD, (*index)++);
	return (0);
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

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
static int	is_special_q(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
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
typedef struct s_parm
{
	t_token	**token;
	char	*input;
	// int		*i;
	int		*index;
	char	*str;
	char 	quote;
	char	*s1;
}	t_parm;

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
	// if (quote == '\'')
	// 	add_token(token, s1, SI_QUOTE, *index);
	// else
	// 	add_token(token, s1, WORD, *index);

int	token_str(t_token **token, char *input, int *i, int *index)
{
	int		start;
	char	*value;
	t_parm	*parm;

	parm = malloc(sizeof(t_parm));
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
		else if (input[i] && input[i] != ' ' && input[i] != '|' &&
			input[i] != '<' && input[i] != '>' ) 
		{
			if (token_str(tokens, input, &i, &index))
				return (0);
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
	return (1);
}

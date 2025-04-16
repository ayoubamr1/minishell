/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/16 15:55:42 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_token **lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_exit(t_token **token)
{
	// printf("***\n");
	// printf("{%p} <> {%s}\n", (*token)->original, (*token)->original);
	// free((*token)->in_add);
	// free((*token)->original);
		printf("\n***s**\n");
	ft_lstclear(token);	
	exit(1);
}
static char	*join_and_free(char *s1, char *s2, t_token **token)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!res)
		ft_exit(token);
	return (res);
}

static char	*parse_inside_quote(char *input, int *i, char quote, t_token **token)
{
	int		start;
	char	*tmp;

	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	tmp = substr(input, start, *i - start);
	if (!tmp)
		ft_exit(token);
	if (input[*i] == quote)
		(*i)++;
	return (tmp);
}

static char	*parse_unquoted_part(char *input, int *i, t_token **token)
{
	int		start;
	char	*tmp;

	start = *i;
	while (input[*i] && input[*i] != '\'' && input[*i] != '"' &&
		!isspace(input[*i]) && input[*i] != '|' &&
		input[*i] != '<' && input[*i] != '>')
		(*i)++;
	tmp = substr(input, start, *i - start);
	if (!tmp)
		ft_exit(token);
	return (tmp);
}

char	*parse_word_with_quotes(char *input, int *i, t_token **token)
{
	char	*final;
	char	*tmp;
	char	quote;

	final = ft_strdup("");
	while (input[*i] && !isspace(input[*i]) &&
		input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[(*i)++];
			tmp = parse_inside_quote(input, i, quote, token);
		}
		else
			tmp = parse_unquoted_part(input, i, token);
		final = join_and_free(final, tmp, token);
	}
	return (final);
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

static int	is_redirection(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC);
}

static int	is_bad_redir_sequence(t_token *t)
{
	if (!t->next)
		return (0);
	if (t->type == REDIR_IN && (t->next->type == PIPE
		|| is_redirection(t->next)))
		return (1);
	if (t->type == REDIR_OUT && (t->next->type == PIPE
		|| is_redirection(t->next)))
		return (1);
	if (t->type == APPEND && (t->next->type == PIPE
		|| is_redirection(t->next)))
		return (1);
	return (0);
}

static int	is_general_syntax_error(t_token *t)
{
	
	if ((t->index == 1 && t->type == PIPE)
		|| (!t->next && t->type == PIPE)
		|| (t->next && t->type == PIPE && t->next->type == PIPE)
		|| is_bad_redir_sequence(t)
		|| (t->type == HEREDOC && (!t->next || t->next->type != WORD))
		|| (is_redirection(t) && (!t->next || t->next->type != WORD)))
		return (1);
			printf("=>> {%p} <> {%s}\n", t->original, t->original);
	return (0);
}

void	syntax_error(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp->next != NULL && tmp)
	{
		if (is_general_syntax_error(tmp))
		{
			printf("syntax error near unexpected token\n");
			ft_exit(tokens);
		}
		tmp = tmp->next;
		
	}
}

void lexer_2(t_token **tokens, char *input, int *i, int *index)
{
	char quote;
	int start;
	char *word;

	if (input[*i] == '>')
		{
			// synatx();
			add_token(tokens, strdup(">"), REDIR_OUT, *index);
			((*i)++, (*index)++);
		}
	else if (input[(*i)] == '|')
	{
		// if (input[(*i) + 1 ] == '|')
		add_token(tokens, strdup("|"), PIPE, (*index));
		((*i)++, (*index)++);
	}
	else if (input[*i] == '<')
	{
		add_token(tokens, strdup("<"), REDIR_IN, (*index));
		((*i)++, index++);
	}
	else if (input[(*i)] == '"' || input[(*i)] == '\'')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			word = parse_word_with_quotes(input, i, tokens);
			add_token(tokens, word, STRING, (*index)++);
			// free(word);
		}
	}
	else
		ft_word(tokens, input, i, index);
		// ft_quote(tokens, input, i, index);
}

void	synatx(t_token **token, char *input, char c, int i, int status)
{
	if (status == 1)
	{
		if (input[i + 2] == c)
			(printf("syntax error near unexpected token `>'"), ft_exit(token));
		else if (input[i + 2] == c)
			(printf("syntax error near unexpected token `<'"), ft_exit(token));
	}
	// else if (status == 2)
	// {
	// 	if ((input [i + 1] == ' ' && input [i + 2] == 'd') ||)
	// }
}
void lexer_1(char *input, t_token **tokens)
{
	int i;
	int index;

	i = 0;
	index = 1;
	printf("**\n");
	// printf("{%s}\n", (*tokens)->content);
	if (*tokens)
		// printf("{%s} - {%p} <> {%s}\n", (*tokens)->content,(*tokens)->original, (*tokens)->original);
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			synatx(tokens, input, '>', i, 1);
			add_token(tokens, strdup(">>"), APPEND, index);
			(i += 2, index++);
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			synatx(tokens, input, '<', i, 1);
			add_token(tokens, strdup("<<"), HEREDOC, index);
			(i += 2, index++);
		}
		else
			lexer_2(tokens, input, &i, &index);
	}
	syntax_error(tokens);
}

int main() ////////////// for test
{
	while(1)
	{
		
    char *input = readline("minishell> ");
	if (!input)
		exit(1);
	t_token *tokens = malloc(sizeof(t_token));
	tokens->original = ft_strdup(input);
	// tokens->content = NULL;
	tokens->next = NULL;
	printf("{%p} <> {%s}\n", tokens->original, tokens->original);

	// tokens->content = input;
    lexer_1(input, &tokens);
	t_token *copy = tokens;
    while (copy)
    {
        printf("Token: {%s} || {%d}\n", copy->content, copy->type);
        copy = copy->next;
    }
	printf ("\n---------------------\n");
	// print_tokens(tokens);
	// while (tokens)
	// {
	// printf ("\n1---------------------\n");
	//     // printf("Token: {%s} ==>  Type: %d, index ==> [%d]\n", tokens->content, tokens->type, tokens->index);
	//     printf("Token: {%s}\n", tokens->content);
	//     tokens = tokens->next;
	// }
	// echo 'hello "yool"' | grep hello > file.txt | ls
	// printf ("\n---------------------\n");
	// t_token *copy = tokens;
	// while (copy)
    // {
    //     printf("Token: %s\n", copy->content);
    //     copy = copy->next;
    // }
	}
	// printf("%d\n", ft_lstsize(tokens));
    return 0;
}

			// add_token(tokens, ft_substr(input, start, start + 1), APPEND, index);
// 


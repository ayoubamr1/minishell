/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/14 14:03:51 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_quote(t_token **tokens, char *input, int *i, int *index)
{
	char quote;
	int start;
	int s = 0;
	int d = 0;

	quote = input[(*i)++];
	if (quote == '\'')
		s++;
	else
		d++;
	start = (*i);
	while (input[(*i)] && input[(*i)] != quote)
		(*i)++;
	// / |< "test"test >|
	while (input[(*i)] && (input[(*i)] != ' '))
		(*i)++;
	// if (!(input[(*i)]) && (input[(*i) - 1] != quote && (input[(*i) - 1] != quote)))
	// 	{
	// 		printf("quote error!");
	// 		exit(1);
	// 	}
	// if (!(input[(*i)]))
	if (quote == '"')
		add_token(tokens, substr(input, start, (*i) - start), d_quote, (*index));
	else
		add_token(tokens, substr(input, start, (*i) - start), s_quote, (*index));
	if (input[(*i)] == quote)
		(*i)++;
		(*index)++;
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

void	syntax_error(t_token **tokens)
{
	t_token *tmp;
	t_token *tmp_2;
	
	tmp = *tokens;
	

	while (tmp)
	{
		
		if ((tmp->index == 1 && tmp->type == PIPE) || ((tmp->index == tmp->max_in) && tmp->type == PIPE))
		{
			printf("inde => %d | max_index => %d | type => %d\n", tmp->index, tmp->max_in, tmp->type);
			printf("syntax error pipe \n");
			exit(1);
		}		
		if (tmp->next && (tmp->type == PIPE && tmp->next->type == PIPE))
		{
			printf("syntax error pipe \n");
			exit(1);
		}
		tmp_2 = tmp;
		tmp = tmp->next;
	}
	// if (tmp_2->type == PIPE)
	
	
}


void lexer_2(t_token **tokens, char *input, int *i, int *index)
{
	char quote;
	int start;

	if (input[*i] == '>')
		{
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
		ft_quote(tokens, input, i, index);
	else
		ft_word(tokens, input, i, index);
}


void lexer_1(char *input, t_token **tokens)
{
	int i;
	int index;

	i = 0;
	index = 1;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(tokens, strdup(">>"), APPEND, index);
			(i += 2, index++);
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(tokens, strdup("<<"), HEREDOC, index);
			(i += 2, index++);
		}
		else
			lexer_2(tokens, input, &i, &index);
	}
	(*tokens)->max_in = index;
	// printf("[%d]\n", (*tokens)->max_in);
	syntax_error(tokens);
}

int main() ////////////// for test
{
	while(1)
	{
		
    char *input = readline("minishell> ");
	t_token *tokens = malloc(sizeof(t_token));
	// tokens->original = ft_strdup(input);
	tokens = NULL;
    lexer_1(input, &tokens);
	t_token *copy = tokens;
    while (copy)
    {
        printf("Token: {%s} |=> inde => %d\n", copy->content, copy->index);
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/09 21:15:45 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void lexer(char *input, t_token **tokens)
{
    int i;
	int index;
	int start;

	i = 0;
	index = 1;
	syntax_error(input, tokens);
	while (input[i])
	{

		if (input[i] == ' ')
			i++;
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
		lexer_2(tokens, &i, input, &index);
	}
}
void	lexer_2(t_token **tokens, int *i, char *input, int *index)
{
	 if (input[(*i)] == '>')
		{
			add_token(tokens, ft_strdup(">"), REDIR_OUT, *index);
			((*i)++, (*index)++);
		}
		else if (input[(*i)] == '<')
		{
			add_token(tokens, ft_strdup("<"), REDIR_IN, *index);
			((*i)++, (*index)++);
		}
		else if (input[(*i)] == '|')
		{
			add_token(tokens, ft_strdup("|"), PIPE, *index);
			((*i)++, (*index)++);
		}
		else if (input[(*i)] == '"' || input[(*i)] == '\'')
		{
			printf("hello\n");
			qoute(tokens, &(*i), input, index);
		}
		else
			ft_word(tokens, &(*i), input, index);
}


int main()
{
    char *input;
	input = readline("minishell> ");
    t_token *tokens;
	tokens = malloc(sizeof(t_token));
	tokens->original = ft_strdup(input);
	printf("{%s}\n", tokens->original);
    tokens = NULL;
    lexer(input, &tokens);
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
	t_token *copy = tokens;
	while (copy)
    {
        printf("Token: %s\n", copy->content);
        copy = copy->next;
    }
    return 0;
}
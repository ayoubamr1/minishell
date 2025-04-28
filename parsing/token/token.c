/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:15:44 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/28 16:59:12 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	clear_token(t_token **lst)
// {
// 	t_token	*n;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		n = (*lst)->next;
// 		free((*lst)->content);
// 		(*lst)->content = NULL;
// 		free(*lst);
// 		*lst = NULL;
// 		*lst = n;
// 	}
// 	*lst = NULL;
// }
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


// void	ft_exit(t_token **token)
// {
// 	(void)**token;
// 	// ft_malloc(0, FREE);
// 	// exit(1);
// }
// static char	*join_and_free(char *s1, char *s2)
// {
// 	char	*res;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	res = ft_strjoin(s1, s2);
// 	// free(s1);
// 	// free(s2);
// 	return (res);
// }

// static char	*parse_inside_quote(char *input, int *i, char quote)
// {
// 	int		start;
// 	char	*tmp;

// 	start = *i;
// 	while (input[*i] && input[*i] != quote)
// 		(*i)++;
// 	tmp = substr(input, start, *i - start);
// 	// if (!tmp)
// 	// 	(free(input), ft_exit(token));
// 	if (input[*i] == quote)
// 		(*i)++;
// 	return (tmp);
// }

// static char	*parse_unquoted_part(char *input, int *i)
// {
// 	int		start;
// 	char	*tmp;

// 	start = *i;
// 	while (input[*i] && input[*i] != '\'' && input[*i] != '"' &&
// 		!ft_isspace(input[*i]) && input[*i] != '|' &&
// 		input[*i] != '<' && input[*i] != '>')
// 		(*i)++;
// 	tmp = substr(input, start, *i - start);
// 	// if (!tmp)
// 	// 	(free(input), ft_exit(token));
// 	return (tmp);
// }

// char	*parse_word_with_quotes(char *input, int *i)
// {
// 	char	*final;
// 	char	*tmp;
// 	char	quote;

// 	final = ft_strdup("");
// 	while (input[*i] && !ft_isspace(input[*i]) &&
// 		input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
// 	{
// 		if (input[*i] == '\'' || input[*i] == '"')
// 		{
// 			quote = input[(*i)++];
// 			tmp = parse_inside_quote(input, i, quote);
// 		}
// 		else
// 			tmp = parse_unquoted_part(input, i);
// 		final = join_and_free(final, tmp);
// 	}
// 	return (final);
// }
static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (res);
}

// static char	*parse_inside_quote(char *input, int *i, char quote)
// {
// 	int		start;
// 	char	*tmp;

// 	start = *i;
// 	while (input[*i] && input[*i] != quote)
// 		(*i)++;
// 	tmp = substr(input, start, *i - start);
// 	if (input[*i] == quote)
// 		(*i)++;
// 	return (tmp);
// }

// static char	*parse_unquoted_part(char *input, int *i)
// {
// 	int		start;
// 	char	*tmp;

// 	start = *i;
// 	while (input[*i] && input[*i] != '\'' && input[*i] != '"' &&
// 		!ft_isspace(input[*i]) && input[*i] != '|' &&
// 		input[*i] != '<' && input[*i] != '>')
// 		(*i)++;
// 	tmp = substr(input, start, *i - start);
// 	return (tmp);
// }

// char	*parse_word_with_quotes(char *input, int *i)
// {
// 	char	*final;
// 	char	*tmp;
// 	char	quote;

// 	final = ft_strdup("");
// 	while (input[*i] && !ft_isspace(input[*i]) &&
// 		input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
// 	{
// 		if (input[*i] == '\'' || input[*i] == '"')
// 		{
// 			quote = input[(*i)++];
// 			tmp = parse_inside_quote(input, i, quote);
// 		}
// 		else
// 			tmp = parse_unquoted_part(input, i);
// 		final = join_and_free(final, tmp);
// 	}
// 	return (final);
// }

// void token_str(t_token **token, char *input, int *i, int *index)
// {
// 	int start;
// 	char quote;
// 	char *temp = ft_strdup(""); // temporary buffer for building the string
// 	char *tmp_expand;

// 	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
// 	{
// 		if (input[*i] == '"' || input[*i] == '\'')
// 		{
// 			quote = input[*i];
// 			(*i)++;
// 			start = *i;
// 			while (input[*i] && input[*i] != quote)
// 			{
// 				if (quote == '"' && input[*i] == '$') // Only expand inside "
// 				{
// 					// tmp_expand = expand_env(input, i); // Expand variable
// 					temp = join_and_free(temp, tmp_expand);
// 				}
// 				else
// 				{
// 					temp = join_and_free(temp, substr(input, *i, 1));
// 					(*i)++;
// 				}
// 			}
// 			if (input[*i] == quote)
// 				(*i)++; // Skip closing quote
// 		}
// 		else
// 		{
// 			start = *i;
// 			while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
// 				(*i)++;
// 			temp = join_and_free(temp, substr(input, start, (*i) - start));
// 		}
// 	}
// 	if (temp[0] != '\0')
// 	{
// 		add_token(token, temp, WORD, (*index));
// 		(*index)++;
// 	}
// }
// ----------------------------------------------------
// void token_str(t_token **token, char *input, int *i, int *index)
// {
// 	int start;
// 	char quote;
// 	char *temp = ft_strdup(""); // Temporary buffer to collect characters

// 	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
// 	{
// 		if (input[*i] == '"' || input[*i] == '\'')
// 		{
// 			quote = input[*i];
// 			(*i)++;
// 			while (input[*i] && input[*i] != quote)
// 			{
// 				temp = join_and_free(temp, substr(input, *i, 1));
// 				(*i)++;
// 			}
// 			if (input[*i] == quote)
// 				(*i)++;
// 		}
// 		else
// 		{
// 			start = *i;
// 			while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
// 				(*i)++;
// 			temp = join_and_free(temp, substr(input, start, (*i) - start));
// 		}
// 	}

// 	if (temp[0] != '\0')
// 	{
// 		add_token(token, temp, WORD, (*index));
// 		(*index)++;
// 	}
// 	else
// 		free(temp);
// }

// void token_str(t_token **token, char *input, int *i, int *index)
// {
// 	int start;
// 	char quote;
// 	char *temp;

// 	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
// 	{
// 		temp = ft_strdup(""); // Reset temp for each token

// 		if (input[*i] == '"' || input[*i] == '\'')
// 		{
// 			quote = input[*i];
// 			(*i)++;

// 			while (input[*i] && input[*i] != quote)
// 			{
// 				temp = join_and_free(temp, substr(input, *i, 1));
// 				(*i)++;
// 			}

// 			if (input[*i] == quote)
// 				(*i)++;

// 			// Save the string inside the quotes as a token
// 			if (temp[0] != '\0')
// 			{
// 				add_token(token, temp, WORD, (*index));
// 				(*index)++;
// 			}
// 			else
// 				free(temp);
// 		}
// 		else
// 		{
// 			start = *i;
// 			while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
// 				(*i)++;

// 			temp = substr(input, start, (*i) - start);

// 			// Save outside quotes token
// 			if (temp && temp[0] != '\0')
// 			{
// 				add_token(token, temp, WORD, (*index));
// 				(*index)++;
// 			}
// 			else
// 				free(temp);
// 		}
// 	}
// }
// -------------

// void *token_str(t_token **token, char *input, int *i, int *index)
// {
//     int     start;
//     char    quote;
//     char    *temp;
    
//     while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
//     {
//         if (input[*i] == '\'' || input[*i] == '"')
//         {
//             quote = input[*i];
//             (*i)++; // Skip opening quote
//             start = *i;
            
//             // Find the closing quote
//             while (input[*i] && input[*i] != quote)
//                 (*i)++;
                
//             if (!input[*i]) // Reached end of string without finding closing quote
//             {
//                 printf("minishell: syntax error: unclosed quote [%c]\n", quote);
//                 return (NULL);
//             }
            
//             // Create token with the content between quotes
//             temp = substr(input, start, (*i) - start);
//             if (!temp)
//                 return (NULL);
                
//             (*i)++; // Skip closing quote
            
//             // Add the token with appropriate type
//             if (temp[0] != '\0') // Handle empty quotes
//             {
//                 if (quote == '\'')
//                     add_token(token, temp, SI_QUOTE, (*index));
//                 else
//                     add_token(token, temp, WORD, (*index));
//                 (*index)++;
//             }
//             else
//                 free(temp);
//         }
//         else
//         {
//             start = *i;
//             // Collect characters until a special character or quote is found
//             while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
//                    input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
//                 (*i)++;
                
//             // Create token with the collected characters
//             temp = substr(input, start, (*i) - start);
//             if (!temp)
//                 return (NULL);
                
//             if (temp[0] != '\0')
//             {
//                 add_token(token, temp, WORD, (*index));
//                 (*index)++;
//             }
//             else
//                 free(temp);
//         }
//     }
//     return (NULL);
// }
void	token_str(t_token **token, char *input, int *i, int *index)
{
	char quote; 
	int start;
	int s;

	start = *i;
	while (input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		s = 1;
		quote = input[*i];
		(*i)++;
		while (input[*i])
		{
			if (input[*i] == quote)
			{
				s++;
				(*i)++;
				break;
			}
			(*i)++;
		}
		while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
			(*i)++;
		if (quote == '\'')
			add_token(token, substr(input, start, (*i) - start), SI_QUOTE, (*index));
		else
			add_token(token, substr(input, start, (*i) - start), WORD, (*index));
		return ;
	}
		add_token(token, substr(input, start, (*i) - start), WORD, (*index));
    return ;
	
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
	char *word;

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

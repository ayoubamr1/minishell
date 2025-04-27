/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/27 14:50:39 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

		// if (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
		// 	input[*i] != '<' && input[*i)] != '>' )
// void	 token_str(t_token **token, char *input, int *i, int *index)
// {
// 	int	start;
// 	int s = 0;
// 	char quote = 0;
// 	start = (*i);
// 	if (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
// 		input[*i] != '<' && input[*i] != '>' )
// 	{

// 	while(input[*i])
// 	{
// 		if (input[*i] == '"' || input[*i] == '\'')
// 		{
// 			quote = input[*i];
// 			// break;
// 		}
// 		(*i)++;
// 		while (input[*i])
// 		{
// 			if (input[*i] == quote && input[(*i) + 1] == ' ')	
// 			{
// 				s = 1;
// 				break;
// 			}
// 			else (input[*i] == quote && input[(*i) + 1])
// 		}
// 	}
// 	if (quote == '\'')
// 	{
// 		add_token(token, substr(input, start, (*i) - start), SI_QUOTE, (*index));
// 		(*index)++;	
// 	}
// 	else
// 	{
// 		add_token(token, substr(input, start, (*i) - start), WORD, (*index));
// 		(*index)++;	
// 	}
// 	}
	
// }
/*  fucntion 1 tkhode liya strige be quote dyalo 
	function 2 tkhode liya tchofe dake string wche fihe $ o fine ja wche single quote or double 
	function 3 te add le tchof $ wache valid
*/



void token_str(t_token **token, char *input, int *i, int *index)
{
	int start;
	char quote;
	char *temp = ft_strdup(""); // temporary buffer for building the string
	char *tmp_expand;

	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			start = *i;
			while (input[*i] && input[*i] != quote)
			{
				// if (quote == '"' && input[*i] == '$') // Only expand inside "
				// {
				// 	// tmp_expand = expand_env(input, i); // Expand variable
				// 	temp = join_and_free(temp, tmp_expand);
				// }
				// else
				// {
					temp = join_and_free(temp, substr(input, *i, 1));
					(*i)++;
				// }
			}
			if (input[*i] == quote)
				(*i)++;
		}
		else
		{
			start = *i;
			while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '"' && input[*i] != '\'')
				(*i)++;
			temp = join_and_free(temp, substr(input, start, (*i) - start));
		}
	}
	if (temp[0] != '\0')
	{
		add_token(token, temp, WORD, (*index));
		(*index)++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:38:29 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/18 17:06:13 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	return (0);
}

static int	close_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
				return (1);
		}	
		i++;
	}
	return (0);
}

int	syntax_error(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (close_quote(tmp->content))
		{
			printf("Syntax error: unclosed quote\n");
			exite_status = 1;
			return (FALSE);
		}
		if (is_general_syntax_error(tmp))
		{
			printf("syntax error near unexpected token\n");
			exite_status = 1;
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

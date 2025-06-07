/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/07 18:52:36 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_ansi_c_quote(char *str, int *i, char *res)
{
	res = strjoin_char(res, str[*i]); // Add $
	(*i)++;
	res = strjoin_char(res, str[*i]); // Add '
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*handle_regular_quotes(char *str, int *i, char *res, char *quot)
{
	if ((str[*i] == '\'' || str[*i] == '"') && *quot == 0)
	{
		*quot = str[*i];
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	else if (str[*i] == *quot)
	{
		*quot = 0;
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*handle_variable_expansion(char *str, int *i, t_env *env, char *res)
{
	if (str[*i] == '$' && str[*i + 1] == '$')
	{
		// res = expand_pid(res, str, *i);
		*i += 2;
	}
	else if (str[*i] == '$' && str[*i + 1] && ft_isalpha(str[*i + 1]) 
	&& !ft_quote(str[*i + 1]))
	{
		if (ft_check_sp(str))
			env->flag = 1;
		res = expand_env_var(str, i, env, res);
	}
	else if (str[*i] == '$' && str[*i + 1] && !ft_isalpha(str[*i + 1]) 
		&& !ft_quote(str[*i + 1]))
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	else
	{
		res = strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*ft_expand_token(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	quot;

	i = 0;
	quot = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\'')
			res = handle_ansi_c_quote(str, &i, res);
		else
		{
			res = handle_regular_quotes(str, &i, res, &quot);
			if (str[i])
				res = handle_variable_expansion(str, &i, env, res);
		}
	}
	return (ft_dolar(res));
}

void	ft_expand(t_shell *shell)
{
	t_token	*tok = shell->token;
	char	*expanded;

	while (tok)
	{
		if ((tok->type == WORD || tok->type == SI_QUOTE) && ft_strchr(tok->content, '$'))
		{
			expanded = remove_quotes(ft_expand_token(tok->content, shell->env));
			
			if (!expanded || !expanded[0])
				tok->content = ft_strdup("");
			else if (shell->env->flag == 1 || !ft_strchr(expanded, ' '))
			{
				tok->content = expanded;
				
			}
			else
				tok = split_token_ex(tok, expanded, shell);
		}
		else if (tok->type == WORD || tok->type == SI_QUOTE)
			tok->content = remove_quotes(tok->content);

		tok = tok->next;
	}	
}

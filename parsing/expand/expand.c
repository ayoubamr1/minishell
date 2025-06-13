/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/13 17:48:55 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_ansi_c_quote(char *str, int *i, char *res)
{
	res = strjoin_char(res, str[*i]);
	(*i)++;
	res = strjoin_char(res, str[*i]);
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

char	*handle_var_expand(char *str, int *i, t_shell *shell, char *res)
{
	if (str[*i] == '$' && str[*i + 1] == '$')
		*i += 2;
	else if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
	{
		*i += 2;
		res = ft_strjoin(res, "$?");
	}
	else if (str[*i] == '$' && str[*i + 1] && ft_isalpha(str[*i + 1])
		&& !ft_quote(str[*i + 1]))
	{
		if (ft_check_sp(str))
			shell->tmp->ex_space_flag = 1;
		res = expand_env_var(str, i, shell->env, res);
	}
	else if (str[*i] == '$' && str[*i + 1] && !ft_isalpha(str[*i + 1])
		&& !ft_quote(str[*i + 1]))
	{
		*i += 2;
		res = strjoin_char(res, str[*i]);
	}
	else
		res = strjoin_char(res, str[(*i)++]);
	return (res);
}

char	*ft_expand_token(char *str, t_shell *shell)
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
				res = handle_var_expand(str, &i, shell, res);
		}
	}
	return (ft_dolar(res));
}

void	ft_expand(t_shell *shell)
{
	t_token	*tok;
	char	*expanded;

	tok = shell->token;
	while (tok)
	{
		if ((tok->type == WORD || tok->type == SI_QUOTE)
			&& ft_strchr(tok->content, '$'))
		{
			shell->tmp = tok;
			expanded = remove_quotes(ft_expand_token(tok->content, shell));
			if (!expanded || !expanded[0])
				tok->content = ft_strdup("");
			else if (tok->ex_space_flag == 1 || !ft_strchr(expanded, ' '))
				tok->content = expanded;
			else
				tok = split_token_ex(tok, expanded, shell);
		}
		else if (tok->type == WORD || tok->type == SI_QUOTE)
			tok->content = remove_quotes(tok->content);
		tok = tok->next;
	}	
}

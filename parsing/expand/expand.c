/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/18 16:18:07 by nbougrin         ###   ########.fr       */
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

char	**ft_split_space(char *str)
{
	char	**new;
	char	quote;
	int		start;
	int		i;

	(1) && (quote = 0, new = NULL, i = 0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		start = i;
		while (str[i] && str[i] != ' ')
		{
			if (ft_quote(str[i]))
			{
				quote = str[i++];
				while (str[i] && str[i] != quote)
					i++;
			}
			i++;
		}
		new = ft_strjoin2d(new, remove_quotes(substr(str, start, i - start)));
	}
	return (new);
}

t_token    *split_token_exx(t_token *tok, char **spl)
{
	t_token	*last;
	t_token	*save;
	int		i;

	if (!spl || !(*spl))
		return(tok);
	save = tok->next;
	tok->content = spl[0];
	i = 1;
	last = tok;
	while (spl[i])
	{
		tok->next = new_token(spl[i++], WORD);
		tok = tok->next;
	}
	tok->next = save;
	return (tok);
}

void    ft_expand(t_shell *shell)
{
	t_token		*tok;
	char		*expanded;
	char		**new;

	tok = shell->token;
	while (tok)
	{
		if (tok->type == WORD || tok->type == SI_QUOTE)
		{
			expanded = ft_expand_token(tok->content, shell);
			char *gg = remove_quotes(expanded);
			if (gg && !gg[0] && shell->env->quot == 1)
			{
				tok->content = expanded;
				tok->type = SKIP;
			}
			else if (!ft_strchr(tok->content, '$'))
				tok->content = remove_quotes(tok->content);
			else if (!ft_strchr(expanded, ' '))
				tok->content = remove_quotes(expanded);
			else
				tok = split_token_exx(tok, ft_split_space(expanded));
		}
		tok = tok->next;
	}
}

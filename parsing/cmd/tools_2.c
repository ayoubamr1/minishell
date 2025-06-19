/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:34:50 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/19 21:28:53 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cmd_2(t_shell *shell, t_token *tmp, t_cmd *cmd_tmp)
{
	while (tmp)
	{
		tmp = store_cmd_node(shell, cmd_tmp, tmp);
		if (tmp && tmp->type == PIPE)
		{
			cmd_tmp = cmd_tmp->next;
			tmp = tmp->next;
		}
	}
}

char	*heredoc_expand(char *str, t_env *env)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
			i += 2;
		else if (str[i] == '$' && str[i + 1] && ft_isalpha(str[i + 1]))
			res = expand_env_var_her(str, &i, env, res);
		else if (str[i] == '$' && str[i + 1] && !ft_isalpha(str[i + 1]))
			res = strjoin_char(res, str[i++]);
		else
			res = strjoin_char(res, str[i++]);
	}
	return (res);
}

void	delimiter_dollar(char *str, char *new, int *i, int *p)
{
	int		d;
	int		j;
	char	qout;

	d = 0;
	while (str[*i] == '$')
		(1) && (d++, (*i)++);
	if (ft_quote(str[*i]) && (d % 2 == 1))
	{
		qout = str[(*i)++];
		j = 0;
		while (j < (d - 1))
			(1) && (new[(*p)++] = '$', j++);
		while (str[*i] && str[*i] != qout)
			new[(*p)++] = str[(*i)++];
		if (str[*i] == qout)
			(*i)++;
	}
	else
	{
		j = 0;
		while (j < d)
			(1) && (new[(*p)++] = '$', j++);
	}
}

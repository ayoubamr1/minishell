/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 18:47:50 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_pid(char *res, char *str, int i)
{
	pid_t	pid;
	char	*pid_str;
	char	*tmp;
	int		start;

	start = i;
	// i = i + 2;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			// printf(">>[%s]\n", substr(str, start, i - start));
			// printf(">>[%s]\n",res);
			// printf(">>[%s]\n",ft_strjoin(res, substr(str, start, i - start)));
			return(ft_strjoin(res, substr(str, start, i - start)));
		}
		i++;
	}
	pid = getpid();
	pid_str = id_itoa(pid);
	if (!pid_str)
		return (res);
	tmp = ft_strjoin(res, pid_str);
	return (tmp);
}

static char	*cher_env(char *key, t_env *env)
{
	t_env	*tmp;
	char	*search;
	size_t	key_len;

	tmp = env;
	// search = ft_strjoin(key, ft_strdup("="));
	key_len = strlen(key);

	while (tmp)
	{
		if (!ft_strncmp(tmp->content, key, key_len))
		{
			return (ft_strdup(tmp->content + key_len));
		}		
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

// static int	is_special_charr(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == '"' || c == '\'' || c == ' ' || c == '$');
// }

static int	is_special_charr(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '$');
}

static char	*expand_env_var(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;
	char 	*env_path;
	int		j;
	int		k;
	int 	p;
	char	quot = 0;
	k = 0;
	while (str[k] && k <= (*i))
	{
		if ((str[k] == '\'' || str[k] == '"') && quot == 0)
			quot = str[k];
		else if (str[k] == quot)
			quot = 0;
		k++;
	}
	start = ++(*i);
	j = 0;
	while (str[*i] && ft_isalpha(str[*i]) && !is_special_charr(str[*i]))
	(*i)++;
	key = substr(str, start, *i - start);
	val = cher_env(key, env);
	if (!val)
		return(NULL);
	if (quot == '\'')
		return(ft_strjoin(res, ft_strjoin("$", key)));
	env_path = ft_malloc(sizeof(val), MALLOC);
	while (val[j] && val[j] != '=')
		j++;
	j++;
	p = 0;
	while (val[j])
		env_path[p++] = val[j++];
	env_path[p] = '\0';
	tmp = ft_strjoin(res, env_path);
	return (tmp);
}

static char *ft_dolar(char *str)
{
	int i;
	int p;
	char *new;
	char qout;

	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			qout = str[i];
			new[p++] = str[i++];
			printf("[%c]==[%c]\n", str[i], qout);
			while (str[i] && str[i] != qout)
				new[p++] = str[i++];
			if (str[i] == qout)
				new[p++] = str[i++];
		}
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
			new[p++] = str[i++];
	}
	new[p] = '\0';
	// printf("new=>[%s]\n", new);
	// exit(0);
	return(new);
}

// static char *ft_dolar(char *str)
// {
//     int i = 0;
//     int p = 0;
//     char *new;
//     char qout;

//     new = ft_malloc(ft_strlen(str) + 1, MALLOC);
//     if (!new)
//         return NULL;

//     while (str[i])
//     {
//         if (str[i] == '"' || str[i] == '\'')
//         {
//             qout = str[i++];
//             while (str[i] && str[i] != qout)
//                 new[p++] = str[i++];
//             if (str[i] == qout)
//                 i++; // skip closing quote
//         }
//         else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
//         {
//             i++; // skip the dollar sign
//         }
//         else
//         {
//             new[p++] = str[i++];
//         }
//     }
//     new[p] = '\0';
//     printf("new>[%s]\n", new);

//     return new;
// }


static char	*ft_expand_token(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			res = expand_pid(res, str, i);
			i += 2;
		}
		else if (str[i] && (str[i] == '$') && str[i + 1] && ft_isalpha(str[i + 1]))
			res = expand_env_var(str, &i, env, res);
		else
		{
			tmp = substr(str, i, 1);
			res = ft_strjoin(res, tmp);
			i++;
		}
	}
		// printf("res=>[%s]\n", res);
	return (ft_dolar(res));
}

void	ft_expand(t_shell *shell)
{
	t_token	*tok;
	char	*expanded;
	char	*dol;

	tok = shell->token;
	while (tok)
	{
		if (tok->type == WORD || tok->type == SI_QUOTE)
		{
			expanded = ft_expand_token(tok->content, shell->env);
			// printf("expanded>[%s]\n", expanded);
			tok->content = remove_quotes(expanded);
		}
		tok = tok->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/02 19:44:31 by nbougrin         ###   ########.fr       */
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

// static char	*expand_env_var(char *str, int *i, t_env *env, char *res)
// {
// 	int		start;
// 	char	*key;
// 	char	*val;
// 	char	*tmp;
// 	char 	*env_path;
// 	int		j;
// 	int		k;
// 	int 	p;
// 	char	quot = 0;
// 	k = 0;
// 	printf("[%c] i= %i\n", str[*i], *i);
// 	while (str[k] && k < (*i))
// 	{
// 		if ((str[k] == '\'' || str[k] == '"') && quot == 0)
// 			quot = str[k];
// 		else if (str[k] == quot)
// 			quot = 0;
// 		k++;
// 	}
// 	printf("%i | %i\n", k, *i);
// 	// printf("%c | %c\n", str[k], str[*i]);
// 	// $'$$"$HOME$"' 
// 	start = (*i)++;
// 	j = 0;
// 	while (str[*i] && ft_isalpha(str[*i]) && !is_special_charr(str[*i]))
// 		(*i)++;
	
// 	key = substr(str, start, *i - start);
// 	val = cher_env(key, env);
// 	// printf("key[%s]==val[%s]\n", key, res);
// 	// exit(0);
// 	// printf("tmp =>%s | key => %s | i=>%i | [%c]\n", res, key, *i, str[]);
// 	if (!val)
// 		return(res);
// 	if (quot == '\'')
// 		return(ft_strjoin(res, ft_strjoin("$", key)));
// 	if (val)
// 	{
// 		env_path = ft_malloc(ft_strlen(val) + 1, MALLOC);
// 		while (val[j] && val[j] != '=')
// 			j++;
// 		if (val[j])
// 			j++;
// 		p = 0;
// 		while (val[j])
// 			env_path[p++] = val[j++];
// 		env_path[p] = '\0';
// 		}
// 	tmp = ft_strjoin(res, env_path);
// 	// printf("%s\n", tmp);
// 	// exit(0);
// 	return (tmp);
// }


static char	*expand_env_var(char *str, int *i, t_env *env, char *res)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;
	char 	*env_path = NULL;
	int		j;
	int		k;
	int 	p;
	char	quot = 0;
	k = 0;
	// printf("{%s}\n", res);
	// exit(0);
	while (str[k] && k < (*i))
	{
		if ((str[k] == '\'' || str[k] == '"') && quot == 0)
			quot = str[k];
		else if (str[k] == quot)
			quot = 0;
		k++;
	}
	// printf("%c | %c\n", str[(*i)++], str[++(*i)]);
	// exit(0);
	// printf("%c | %c\n", str[k], str[*i]);
	// $ ' $ $ " $ H O M E $ " '
	// 0 1 2 3 4 5 6  
	start = ++(*i);
	j = 0;
	while (str[*i] && ft_isalpha(str[*i]) && !is_special_charr(str[*i]))
		(*i)++;
	
	key = substr(str, start, *i - start);
	val = cher_env(key, env);
	// printf("key[%s]==res[%s]\n", key, res);
	// printf("tmp =>%s | key => %s | i=>%i | [%c]\n", res, key, *i, str[]);
	if (!val)
		return(res);
	if (quot == '\'')
		return(ft_strjoin(res, ft_strjoin("$", key)));
	if (val)
	{
		env_path = ft_malloc(ft_strlen(val) + 1, MALLOC);
		while (val[j] && val[j] != '=')
			j++;
		if (val[j])
			j++;
		p = 0;
		while (val[j])
			env_path[p++] = val[j++];
		env_path[p] = '\0';
		}
	tmp = ft_strjoin(res, env_path);
	// printf("%s\n", tmp);
	// exit(0);
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
	// printf(">>%s\n", str);
	while (str[i] )
	{
		if (str[i] &&  str[i] == '"' || str[i] == '\'')
		{
			new[p++] = str[i];
			qout = str[i++];
			while (str[i] && str[i] != qout)
				new[p++] = str[i++];
			if (str[i] == qout)
				new[p++] = str[i++];
			new[p] = '\0';	
			// printf("[%s] [%i]\n", new, i);
			// exit(0);
		}
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
			new[p++] = str[i++];
	}
	new[p] = '\0';
	// printf("|=[%s]\n", new);
	// exit(0);
	return(new);
}

static int ft_quote(char c)
{
	return (c == '"' || c == '\'');
}
static char *strjoin_char(char *str, char c)
{
    size_t len;

	len = 0;
    if (str)
        len = ft_strlen(str);
    char *new_str = ft_malloc(len + 2, MALLOC);
    if (str)
        memcpy(new_str, str, len);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return (new_str);
}

static char	*handle_ansi_c_quote(char *str, int *i, char *res)
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

static char	*handle_regular_quotes(char *str, int *i, char *res, char *quot)
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

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	size;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	size = end - start;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, size + 1);
	return (str);
}

static int ft_check_sp(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return(1);
		i++;
	}
	// i = 0;
	// int j = 0;
	// char *new = ft_malloc(MALLOC, ft_strlen(str) + 1);
	// while (str[i])
	// {	
	// 	while (str[i] && str[i] == ' ')
	// 		i++;
	// 	while (str[i] && str[i] != ' ')
	// 		new[j++] = str[i++];
	// 	while (str[i] && str[i] == ' ')
	// 		i++;
	// 	if (str[i++]);
	// 		new[j++] = ' ';
	// }
	// new[j] = '\0';	
	return(0);
}
static int ft_cc(char *str, int *i)
{
	int k = 0;
	char quot = 0;
	
	while (str[k] && k < (*i))
	{
		if ((str[k] == '\'' || str[k] == '"') && quot == 0)
		quot = str[k];
		else if (str[k] == quot)
		quot = 0;
		k++;
	}
	if (quot == '"')
		return(0);
	else
		return(1);
}
	// export b="      ls     bbbb"
static char *ft_char_sp(char *str)
{
	char	*new;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	new = ft_malloc(ft_strlen(str) + 1, MALLOC);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
			new[j++] = str[i++];
		if (str[i]) // There are more characters ahead
			new[j++] = ' ';

		while (str[i] == ' ')
			i++;
	}
	if (j > 0 && new[j - 1] == ' ')
		j--; 
	new[j] = '\0';
	return (new);
}


static char	*handle_variable_expansion(char *str, int *i, t_env *env, char *res)
{
	char *status_str;
	if (str[*i] == '$' && str[*i + 1] == '$')
	{
		res = expand_pid(res, str, *i);
		*i += 2;
	}
	else if (str[*i] == '$' && str[*i + 1] == '?')
	{
		status_str = ft_itoa(g_exit_status);
		res = ft_strjoin(res, status_str);
		i += 2;
	}
	else if (str[*i] == '$' && str[*i + 1] && ft_isalpha(str[*i + 1]) 
		&& !ft_quote(str[*i + 1]))
	{
		// if (!ft_check_sp(str))
		// 	res = ft_strtrim(expand_env_var(str, i, env, res), " ");
		if (ft_cc(str, i))
		{
			char *envv = expand_env_var(str, i, env, res);
			char *test = ft_char_sp(envv);
			res = ft_strjoin(res,test );
			// printf("env[%s] || res[%s]\n", envv, res);
			// exit(0);
		}
		else
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
		{
			res = handle_ansi_c_quote(str, &i, res);
		}
		else
		{
			res = handle_regular_quotes(str, &i, res, &quot);
			if (str[i])
				res = handle_variable_expansion(str, &i, env, res);
		}
	}
	// exit(0);
	return (ft_dolar(res));
}

// char	*ft_expand_token(char *str, t_env *env)
// {
// 	int		i;
// 	char	*res;
// 	char	*tmp;

// 	i = 0;
// 	res = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '$')
// 		{
// 			res = expand_pid(res, str, i);
// 			i += 2;
// 		}
// 		else if (str[i] && (str[i] == '$') && str[i + 1] && ft_isalpha(str[i + 1]) && !ft_quote(str[i + 1]))
// 		{
// 			res = expand_env_var(str, &i, env, res);
// 		}
			
// 		else if(str[i] && i > 0 && (str[i] == '$' && str[i - 1] != '$') && str[i + 1] && !ft_isalpha(str[i + 1]) && !ft_quote(str[i + 1]))
// 			i += 2;
// 		else
// 		{
// 			res = strjoin_char(res, str[i]);
// 			i++;
// 		}
// 	}
// 	return (ft_dolar(res));
// }

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
			// printf("tok>[%s]\n", expanded);
			tok->content = remove_quotes(expanded);
		}
		tok = tok->next;
	}
}

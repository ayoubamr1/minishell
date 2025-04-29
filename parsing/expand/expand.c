/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:02:09 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/29 15:18:52 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
 
// static char *cher_env(char *str, t_env *env)
// {
// 	int i = 0;
// 	t_env *ee = env;
// 	char *tmp = ft_strjoin(str, "=");
// 	while (ee)
// 	{
		
// 		if (!strncmp(str, ee->content, strlen(str)))
// 		{
// 			while (ee->content[i] != '=')
// 				i++;
// 			i++;
// 			char *tm = substr(ee->content, i, ((int)strlen(ee->content)) - i);
// 			return(tm);
// 			exit(0);
// 		}
// 		ee = ee->next;
// 	}
// 	return(NULL);
// }

// static char	*ft_wor(char *str, t_env *env)
// {
// 	int i = 0;
// 	int q = 0;
// 	int dolare;
// 	int start;
// 	char *tmp_1;

// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 			q++, i++;
// 		if (str[i] == '$' && q == 1 && str[i + 1])
// 		{
// 			dolare = i;
// 			tmp_1 = substr(str, 0, dolare);
// 			printf("tmp => [%s]", tmp_1);
// 			start = i + 1;
// 			while (str[i] && str[i] != ' ' && str[i] != '"')
// 				i++;
// 			char *tmp_2 = cher_env(substr(str, start, i - start), env);
// 			return(ft_strjoin(tmp_1, tmp_2)); 
// 		}
// 		i++;
// 	}
	
// 	return(0);
// }

// void	ft_expand(t_shell	*shell_list)
// {
// 	t_env *env = shell_list->env;
// 	t_token *tok = shell_list->token;

// 	char qoute;
// 	int i = 0;
// 	while (tok)
// 	{
// 		if (tok->type == WORD)
// 		{
// 			tok->content = ft_wor(tok->content, shell_list->env);
// 				printf(">>[%s]\n", tok->content);
// 		}
// 		tok = tok->next;
// 		/* code */
// 	}
// 	// `
// 	// while (env)
// 	// {

// 	// }
	
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
static char *cher_env(char *key, t_env *env)
{
	t_env *cur = env;
	char *search = ft_strjoin(key, "=");
	size_t key_len = strlen(key);

	while (cur)
	{
		if (!strncmp(search, cur->content, key_len + 1))
		{
			free(search);
			return ft_strdup(cur->content + key_len + 1);
		}
		cur = cur->next;
	}
	free(search);
	return ft_strdup("");
}

static char *ft_expand_token(char *str, t_env *env)
{
	int i = 0;
	char *res = ft_strdup("");
	char *tmp, *key, *val;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			int start = ++i;
			while (str[i] && (isalnum(str[i]) || str[i] == '_'))
				i++;

			key = substr(str, start, i - start);
			val = cher_env(key, env);
			free(key);

			tmp = join_and_free(res, val);
			res = tmp;
		}
		else
		{
			tmp = substr(str, i, 1);
			res = join_and_free(res, tmp);
			i++;
		}
	}
	return res;
}

void ft_expand(t_shell *shell)
{
	t_token *tok = shell->token;

	while (tok)
	{
		if (tok->type == WORD)
		{
			char *expanded = ft_expand_token(tok->content, shell->env);
			free(tok->content);
			tok->content = expanded;
		}
		tok = tok->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:48:23 by ayameur           #+#    #+#             */
/*   Updated: 2025/06/20 17:04:44 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_shell *main, char *key, char *value)
{
	t_env	*cur;
	char	*new_pwd;
	size_t	key_len;
	
	key_len = ft_strlen(key);
	new_pwd = ft_strjoin(ft_strjoin(key, "="), value);
	// printf("newpwd in update_env = %s\n", new_pwd);
	cur = main->env;
	while (cur)
	{
		if (ft_strncmp(cur->content, key, key_len) == 0 && cur->content[key_len] == '=')
		{
			// free(cur->content);
			cur->content = new_pwd;
			// printf("content here = %s\n", cur->content);
			return ;
		}
		cur = cur->next;
	}
	add_to_env(main, new_pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/23 19:49:31 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char **build_args(t_token **token)
{
	t_token *tmp;
	char	**args;
	int		args_count;
	int		i;

	tmp = *token;
	args_count = 0;
	i = 0;
	while(tmp)
	{
		if (tmp->type == WORD || tmp->type == STRING)
			args_count++;
		tmp = tmp->next;
	}
	args = ft_malloc((size_t)(sizeof(char *) * (args_count + 1)), MALLOC);
	tmp = *token;
	while (tmp &&  (tmp->type == WORD || tmp->type == STRING))
	{
			args[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return(args);
}
void	ft_commend(t_token **token, t_cmd **cmd_list)
{
	t_token *tmp;
	t_cmd	*cmd_tmp = NULL;
	int		pipe_count;
	int		fd = 0;

	tmp = *token;
	cmd_tmp = *cmd_list;
	pipe_count = 1;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe_count++;
		tmp = tmp->next;
	}
	tmp = *token;

	//     	REDIR_IN,   // < check if find this file
    // 		REDIR_OUT,  // > create file
	while(pipe_count >= 1)
	{
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == WORD || tmp->type == STRING)
			{
				cmd_tmp->args = build_args(token);
				int i = 0;
				while (tmp && (tmp->type == WORD || tmp->type == STRING))
					tmp = tmp->next;
			}
			else if (tmp && tmp->type == REDIR_IN)
			{
				tmp = tmp->next;
				fd = open(tmp->content, O_RDWR);
				if (fd < 0)
					perror(tmp->next->content);
				cmd_tmp->in = fd;
				tmp = tmp->next;
			}
			else if (tmp && tmp->type == REDIR_OUT)
			{
				tmp = tmp->next;
				// fd = open(tmp->content,  O_CREAT ,O_RDWR, O_TRUNC, 777);
				fd = open(tmp->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				printf("fd_in =[%d] <> file[%s]\n", fd, tmp->content);
				// printf("fd_out =[%d]\n", fd);
				
				if (fd < 0)
					perror(tmp->content);
				cmd_tmp->out = fd;
				tmp = tmp->next;
			}		
		}
		// tmp = tmp->next;
		pipe_count--;

	
// access();
// execve();
	}
	// 	printf("***********\n");
	// if (tmp && tmp->next && (tmp->next->content[0] == '-'))
	// {
	// 	add_token(commend_list, ft_strjoin(ft_strjoin(tmp->content, " "), tmp->next->content), VOID, 0);
	// 	tmp = tmp->next->next;
	// 	printf("{%s}\n", (*commend_list)->content);
	// }
	// while (tmp && tmp->type != PIPE)
	// {
	// 	if (tmp->type == WORD)
	// 	{
	// 		// if ()
	// 			add_token(commend_list, ft_strjoin(ft_strjoin(tmp->content, " "), tmp->next->content), VOID, 0);
	// 	}
	// 	else if ((tmp->type == REDIR_IN) || (tmp->type == REDIR_OUT))
	// 	{
			
	// 	} 
	// 		tmp = tmp->next;
	// }
	return;
}


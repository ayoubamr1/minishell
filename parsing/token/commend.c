/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbougrin <nbougrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/04/25 12:50:27 by nbougrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd *ft_lstnew(void)
{
	t_cmd *node = malloc(sizeof(t_cmd));
	if (!node)
		return NULL;
	node->args = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->in = -1;
	node->out = -1;
	node->append = 0;
	node->heredoc = 0;
	node->next = NULL;
	return node;
}

static int	ft_lstsize(t_cmd *lst)
{
	int		count;
	t_cmd	*sin;

	sin = lst;
	count = 0;
	while (sin)
	{
		sin = sin->next;
		count++;
	}
	return (count);
}

// static void	ft_lstclear(t_cmd **lst)
// {
// 	t_cmd	*n;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		n = (*lst)->next;
// 		free((*lst)->args);
// 		free(*lst);
// 		*lst = n;
// 	}
// 	*lst = NULL;
// }

static t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

static void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*final;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	final = ft_lstlast(*lst);
	final->next = new;
	return ;
}



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
	char *str  = malloc(sizeof("hello\n") + 1);
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
		if (tmp->type == PIPE)
		{
			printf("FIND PIPE\n");
			tmp = tmp->next;
		}
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == WORD || tmp->type == STRING)
			{
				cmd_tmp = ft_lstnew();
				ft_lstadd_back(cmd_list, cmd_tmp);
				cmd_tmp->args = build_args(&tmp);
				while (tmp && (tmp->type == WORD || tmp->type == STRING))
					tmp = tmp->next;
			}
			else if (tmp && tmp->type == REDIR_IN)
			{
				tmp = tmp->next;
				fd = open(tmp->content, O_RDWR);
				cmd_tmp->infile = ft_strdup(tmp->content);
				if (fd < 0)
					perror(tmp->next->content);
				cmd_tmp->in = fd;
				tmp = tmp->next;
			}
			else if (tmp && tmp->type == REDIR_OUT)
			{
				tmp = tmp->next;
				fd = open(tmp->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				cmd_tmp->outfile = ft_strdup(tmp->content);
				if (fd < 0)
					perror(tmp->content);
				cmd_tmp->out = fd;
				tmp = tmp->next;
			}		
		}
		pipe_count--;

	
	}
	return;
}
// access();
// execve();


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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayameur <ayameur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:15:23 by nbougrin          #+#    #+#             */
/*   Updated: 2025/06/05 15:49:58 by ayameur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*handle_redir_in(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_RDONLY);
	if (fd < 0)
		perror(start->content);
	node->file = ft_strdup(start->content);
	close(node->in);
	node->in = fd;
	return (start->next);
}

static t_token	*handle_redir_out(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		perror(start->content);
	node->file = ft_strdup(start->content);
	close(node->out);
	node->out = fd;
	return (start->next);
}

static t_token	*handle_redir_append(t_cmd *node, t_token *start)
{
	int	fd;

	start = start->next;
	fd = open(start->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		perror(start->content);
	node->file = ft_strdup(start->content);
	close(node->out);
	node->out = fd;
	return (start->next);
}

static	int	len_n(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = len_n(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}

// static int	handle_heredoc(char	*delimiter) 
// {
// 	static size_t hrc_pid = 0;

// 	if (hrc_pid == 0)
// 		hrc_pid = getpid();
// 	else
// 		hrc_pid++;

// 	// Generate filename
// 	char *id_str = ft_itoa(hrc_pid);
// 	char *filepath = ft_strjoin("/tmp/", id_str);
// 	free(id_str);

// 	int fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		free(filepath);
// 		return (-1);
// 	}

// 	while (1)
// 	{
// 		char *line = readline("> ");
// 		if (!line || strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	free(filepath);
// 	char *str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("[%s]\n", str);
// 		str = get_next_line(fd);
// 	}
// 	return (fd); // Return file descriptor to read from later
// }

// char *handle_heredoc(t_shell *shell, char *delimiter) 
// {
// 	// static size_t	hrc_pid;
// 	char			*id_str;
// 	char			*filepath;
// 	int				fd;

// 	static size_t hrc_pid = 0;
// 	if (hrc_pid == 0)
// 		hrc_pid = getpid();
// 	else
// 		hrc_pid++;
// 	id_str = ft_itoa(hrc_pid);
// 	filepath = ft_strjoin("/tmp/", id_str);
// 	free(id_str);
// 	fd = open(filepath, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (NULL);
// 	}
// 	while (1)
// 	{
// 		char *line = readline("> ");
// 		if (!line || strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		// line = ft_expand_token(line, env);
// 		int i = 0;
// 		while (line[i])
// 		{
// 			if (line[i] == '$')
// 			{
// 				line = ft_expand_token(line, shell->env);
// 				break;
// 			}
// 			i++;
// 		}
			
// 		write(fd, line, strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	// lseek(fd, 0, SEEK_SET);
// 	return (filepath);
// }



static t_token	*store_cmd_node(t_shell *shell, t_cmd *node_to_fill, t_token *start)
{
	if (!start)
		return (NULL);
	
	int fd;
	while (start && start->type != PIPE)
	{
		if (start->type == WORD || start->type == SI_QUOTE)
		{
			node_to_fill->cmd = ft_strjoin2d(node_to_fill->cmd, start->content);
			start = start->next;
		}
		else if (start && start->type == REDIR_IN)
			start = handle_redir_in(node_to_fill, start);
		else if (start && start->type == REDIR_OUT)
			start = handle_redir_out(node_to_fill, start);
		else if (start && start->type == APPEND)
			start = handle_redir_append(node_to_fill, start);
		else if (start && start->type == HEREDOC)
		{
			start = start->next;
			fd = open(handle_heredoc(shell, start->content), O_RDONLY);
			if (fd > 0)
				node_to_fill->in = fd;
			else
				return (NULL);
			start = start->next;
		}
	}
	return (start);
}


static void remove_empty_tokens(t_token **head)
{
	t_token *curr;
	t_token *prev;
	t_token *tmp;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (!curr->content || curr->content[0] == '\0')
		{
			tmp = curr;
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			curr = curr->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	ft_edit_redirections(t_cmd *head) 
{
	t_cmd *current;
	
	current = head;
	while (current) 
	{
		if (current == head && current->in == -1337)
		{
			current->in = open("/dev/stdin", O_RDONLY);
			if (current->in == -1)
				perror("open");
		} 
		if (!current->next && current->out == -1337)
		{
			current->out = open("/dev/stdout", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (current->out == -1)
				perror("open");
		}
		current = current->next;
	}
}

t_cmd	*ft_cmd(t_shell *shell, t_token **token, t_cmd **cmd_list, t_env *env)
{
	t_token	*tmp;
	t_cmd	*head;
	t_cmd	*cmd_tmp;

	remove_empty_tokens(token);
	tmp = *token;
	cmd_tmp = ft_lstnew_cmd();
	head = cmd_tmp;
	ft_lstadd_back_cmd(cmd_list, cmd_tmp);
	while (tmp)
	{
		tmp = store_cmd_node(shell, cmd_tmp, tmp);
		if (tmp && tmp->type == PIPE)
		{
			cmd_tmp = ft_lstnew_cmd();
			ft_lstadd_back_cmd(cmd_list, cmd_tmp);
			tmp = tmp->next;
		}
	}
	ft_edit_redirections(head);
	return (head);
}

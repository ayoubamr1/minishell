#include "../../minishell.h"


static int	is_redirection(t_token *token)
{
	return (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC);
}

static int	is_bad_redir_sequence(t_token *t)
{
	if (!t->next)
		return (0);
	if (t->type == REDIR_IN && (t->next->type == PIPE
		|| is_redirection(t->next)))
		return (1);
	if (t->type == REDIR_OUT && (t->next->type == PIPE
		|| is_redirection(t->next)))
		return (1);
	if (t->type == APPEND && (t->next->type == PIPE
		|| is_redirection(t->next)))
		return (1);
	return (0);
}

static int	is_general_syntax_error(t_token *t)
{
	if ((t->index == 1 && t->type == PIPE)
		|| (!t->next && t->type == PIPE)
		|| (t->next && t->type == PIPE && t->next->type == PIPE)
		|| is_bad_redir_sequence(t)
		|| (t->type == HEREDOC && (!t->next || t->next->type != WORD))
		|| (is_redirection(t) && (!t->next || t->next->type != WORD)))
		return (1);
	return (0);
}

void	syntax_error(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (is_general_syntax_error(tmp))
		{
			printf("syntax error near unexpected token\n");
			ft_malloc(0, FREE);
		}
		tmp = tmp->next;
	}
}




























// void	synatx(t_token **token, char *input, char c, int i, int status)
// {
// 	if (status == 1)
// 	{
// 		if (input[i + 2] == c)
// 			(printf("syntax error near unexpected token `>'"), ft_exit(token));
// 		else if (input[i + 2] == c)
// 			(printf("syntax error near unexpected token `<'"), ft_exit(token));
// 	}
// 	// else if (status == 2)
// 	// {
// 	// 	if ((input [i + 1] == ' ' && input [i + 2] == 'd') ||)
// 	// }
// }
















































































// // void syntax_error(char *input, t_token **tokens, int status)
// void syntax_error(char *input, t_token **tokens)
// {
// 	int i;
// 	i = 0;
// 	// if (status == 1)
// 	// {
// 		while (input[i] == ' ') // skip space
// 			i++;
// 		if (input[i] == '|') // check | is first this is syntax error
// 		{
// 			printf("syntax error pipe\n");
// 			ft_exit (tokens);
// 		}
// 	// }
// 	// else ()
// 	// {
// 		pipe_check(tokens);
// 	// }
	

// 	// if (input[i + 1 ] == '|')
// 	// 		{
// 	// 			printf("syntax error pipe\n");
// 	// 			exit (1);
// 	// 		}
// }
// t_token	*ft_lstlast(t_token *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }
// int	ft_lstsize(t_token *lst)
// {
// 	int		count;
// 	t_token	*sin;

// 	sin = lst;
// 	count = 0;
// 	while (sin)
// 	{
// 		sin = sin->next;
// 		count++;
// 	}
// 	return (count);
// }
// void pipe_check(t_token **tokens)
// {
// 	// printf("%s\n", ft_lstlast(*tokens));
// 	int i;
// 	t_token *tmp;
// 	i = 0;
// 	tmp = *tokens;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 		{
// 			if (!tmp->next || (tmp->next->type == PIPE))
// 			{
// 				printf("syntax error: unexpected end after `|'\n");
// 				ft_exit(tokens);
// 			}
// 			// if (tmp->next->type == PIPE)
// 			// {
// 			// 	printf("syntax error: unexpected token `|'\n");
// 			// 	ft_exit(tokens);
// 			// }
// 		}
// 		tmp = tmp->next;
// 	}	

// }

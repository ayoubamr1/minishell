#include "../minishell.h"

// void syntax_error(char *input, t_token **tokens, int status)
void syntax_error(char *input, t_token **tokens)
{
	int i;
	i = 0;
	// if (status == 1)
	// {
		while (input[i] == ' ') // skip space
			i++;
		if (input[i] == '|') // check | is first this is syntax error
		{
			printf("syntax error pipe\n");
			exit (1);
		}
	// }
	// else ()
	// {
		pipe_check(tokens);
	// }
	

	// if (input[i + 1 ] == '|')
	// 		{
	// 			printf("syntax error pipe\n");
	// 			exit (1);
	// 		}
}
t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
int	ft_lstsize(t_token *lst)
{
	int		count;
	t_token	*sin;

	sin = lst;
	count = 0;
	while (sin)
	{
		sin = sin->next;
		count++;
	}
	return (count);
}
void pipe_check(t_token **tokens)
{
	// printf("%s\n", ft_lstlast(*tokens));
	int i;
	t_token *tmp;
	i = 0;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next)
			{
				printf("syntax error: unexpected end after `|'\n");
				exit(1);
			}
			if (tmp->next->type == PIPE)
			{
				printf("syntax error: unexpected token `|'\n");
				exit(1);
			}
		}
		tmp = tmp->next;
	}	

}
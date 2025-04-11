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
void pipe_check(t_token **tokens)
{
	int i;
	t_token *tmp;
	tmp = *tokens;
	while (tmp)
	{
		if(tmp->type == 2)
		{
			printf("good\n");
		}
		tmp = tmp->next;
	}
	

}
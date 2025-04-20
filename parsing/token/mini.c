#include "../../minishell.h"

int main()
{
    char *input;
    t_token *token = NULL;
    t_token *sh = NULL;

    while (1)
    {
        
		token = NULL;
        input = readline("minishell> ");
        if (!input)
            exit(0);

        if (!ft_strncmp(input, "exit", ft_strlen("exit")))
        {
            free(input);
            // ft_lstclear(&token);
            exit(1);
        }
        	lexer_1(input, &token);
		sh = token;
			while (sh)
			{
				printf("index = %d\t content = %s\ttype = %d\n", sh->index, sh->content, sh->type);
				// printf("==> %s\n", sh->content);
				sh = sh->next;
			}
			

        free(input);
		// ft_lstclear(&shell_list);
	
    }
    
    return 0;
}

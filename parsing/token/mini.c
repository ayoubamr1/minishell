#include "../../minishell.h"

int main()
{
    char *input;
    t_token *token = NULL;
    t_cmd *commend_list = ft_malloc((size_t)(sizeof(t_cmd)), MALLOC);
    t_token *sh = NULL;

    while (1)
    {
		token = NULL;
        input = readline("minishell> ");
		add_history(input);
        if (!input)
            exit(0);

        if (!ft_strncmp(input, "exit", ft_strlen("exit")))
        {
            // free(input);
            // ft_lstclear(&token);
            exit(1);
        }
		lexer_1(input, &token);
		if (syntax_error(&token) == TRUE)

		ft_commend(&token, &commend_list);
		t_cmd *cc = commend_list;
		while (cc)
		{
			int i = 0;
			while(cc->args && cc->args[i])
			{
				printf ("{args[%s] ,", cc->args[i]);
				i++;
			}
			if (cc->args)
				printf("infile[%s] outfile[%s] infd[%d] outfd[%d] }\n",cc->infile, cc->outfile, cc->in, cc->out);
			cc = cc->next;
		}
		
		// sh = token;
		// 	while (sh)
		// 	{
		// 		printf("content = %s\n", sh->content);
		// 		// printf("==> %s\n", sh->content);
		// 		sh = sh->next;
		// 	}
		// ft_malloc(0, FREE);
        free(input);
		// ft_lstclear(&shell_list);
    }
    return 0;
}

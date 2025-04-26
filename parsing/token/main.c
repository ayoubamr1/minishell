#include "../../minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    char *input;
    t_token *token = NULL;
    t_cmd *cmd_list;
    t_token *sh = NULL;
    t_shell *shell_list = malloc(sizeof(t_shell));

    while (1)
    {
		token = NULL;
        input = readline("minishell> ");
		if (input[0])
		{
			add_history(input);
			if (!input)
				exit(0);
			cmd_list = ft_malloc((size_t)(sizeof(t_cmd)), MALLOC);
			if (!ft_strncmp(input, "exit", ft_strlen("exit")))
			{
				// free(input);
				// ft_lstclear(&token);
				exit(1);
			}
			lexer_1(input, &token);
			if (syntax_error(&token) == TRUE)
				ft_commend(&token, &cmd_list);
			t_cmd *cc = cmd_list;
			// t_env *env_list; 

			// shell_list->env = ft_env(shell_list->env, env);
			// while (shell_list->env)
			// {
			// 	printf("[%s]\n", shell_list->env->content);
			// 	shell_list->env = shell_list->env->next;
			// }
			while (cc)
			{
				int i = 0;
				while(cc->args && cc->args[i])
				{
					printf ("{args[%s] ,", cc->args[i]);
					i++;
				}
				if (cc->args)
					printf("file[%s] infd[%d] outfd[%d] }\n",cc->file, cc->in, cc->out);
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
    }
    return 0;
}

#include "../../minishell.h"


static void	ft_null(t_shell *shell)
{
	shell->env = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
}

static void	print_node(t_shell *shell_list, char **env)
{
	t_cmd	*cc;

	cc = shell_list->cmd;
	(void)env;
	while (cc)
	{
		int	i;

		i = 0;
		printf("{");
		while (cc->cmd && cc->cmd[i])
		{
			printf("cmd[%s] ,", cc->cmd[i]);
			i++;
		}
		printf("file[%s] infd[%d] outfd[%d] }\n", cc->file, cc->in, cc->out);
		cc = cc->next;
	}
	printf("---------------------------------------------\n");
	// t_token *sh = shell_list->token;

	// while (sh)
	// {
	// 	printf("cont = [%s] type[%d] index[%d]}\n", sh->content, sh->type, sh->index);
	// 	sh = sh->next;
	// }
	// printf("---------------------------------------------\n");
}

void	minishell(t_shell *shell_list, char **env)
{
	char	*input;

	// if (shell_list->token != NULL)
	// 	clear_token(&shell_list->token);
	// if (shell_list->cmd != NULL)
	// 	clear_cmd(&shell_list->cmd);
	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	input = readline("minishell> ");
	if (input)
	{
		add_history(input);
		if (!ft_strncmp(input, "exit", ft_strlen("exit")))
		{
			free(input);
			ft_malloc(0, FREE);
			exit(0);
		}
		lexer_1(input, &shell_list->token);
		if (syntax_error(&shell_list->token) == TRUE)
		{
			shell_list->env = ft_env(shell_list->env, env);
			
			ft_expand(shell_list);
			// exit(0);
			shell_list->cmd = ft_malloc(sizeof(t_cmd), MALLOC);
			shell_list->cmd = ft_cmd(&shell_list->token, &shell_list->cmd);
			print_node(shell_list, env);
		}
	}
	free(input);
}

// static void	handle_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);      // Move to a new line
// 		rl_on_new_line();                  // Notify readline about the new line
// 		rl_replace_line("", 0);           // Clear the current input line
// 		rl_redisplay();                  // Redisplay the prompt
// 	}
// }
int	main(int ac, char **av, char **env)
{
	t_shell	*shell_list;

	(void)ac;
	(void)av;
	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	ft_null(shell_list);
	// signal(SIGINT, handle_sigint);  // This assumes you have a signal handler
	// signal(SIGQUIT, SIG_IGN);
	
	while (1)
	{
		minishell(shell_list, env);
	}
	
	// This part would only be reached if the loop is broken
	// ft_malloc(0, FREE);
	return (0);
}
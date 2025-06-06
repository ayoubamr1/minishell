#include "../../minishell.h"


int exite_status ;
static void	ft_null(t_shell *shell)
{
	// shell->env = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
}

void	print_node(t_shell *shell_list, char **env)
{
	t_cmd	*cc;
	printf("---------------------------------------------\n");

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
		printf("file[%s] infd[%d] outfd[%d] is_bultins[%d]}\n", cc->file, cc->in, cc->out, cc->is_builtin);
		char *str = get_next_line(cc->heredoc);
		while (cc->heredoc > 0 && str)
		{
			printf("get=>[%s]", str);
			str = get_next_line(cc->heredoc);
		}
		cc = cc->next;
		printf("---------------------------------------------\n");
	}
	// t_token *sh = shell_list->token;

	// while (sh)
	// {
	// 	if (!sh->content[0])
	// 		printf("ayaye\n");
	// 	printf("cont = [%s] type[%d] index[%d]}\n", sh->content, sh->type, sh->index);
	// 	sh = sh->next;
	// }
	// printf("---------------------------------------------\n");
}



void	minishell(t_shell *shell_list, char **env)
{
	char	*input;
	int i = 0;
	// if (shell_list->token != NULL)
	// 	clear_token(&shell_list->token);
	// if (shell_list->cmd != NULL)
	// 	clear_cmd(&shell_list->cmd);
	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	shell_list->env = ft_env(shell_list->env, env);
	// hundle_shlvl(shell_list);
	while (TRUE)
	{
		reset_signals_inshild();
		input = readline("minishell> ");
		if (!input)
			exit(0);
		if (input)
		{
			ft_null(shell_list);
			add_history(input);
			// if (!ft_strncmp(input, "exit", ft_strlen("exit")))
			// {
			// 	free(input);
			// 	ft_malloc(0, FREE);
			// 	exit(0);
			// }
			lexer_1(input, &shell_list->token);
			if (syntax_error(&shell_list->token) == TRUE)
			{
				
				ft_expand(shell_list);
				shell_list->cmd = ft_malloc(sizeof(t_cmd), MALLOC);
				shell_list->cmd = ft_cmd(shell_list,  &shell_list->token, &shell_list->cmd, shell_list->env);
				print_node(shell_list, env);
				// printf("||||||||||||||||||||||||||||||||\n");
				execution(shell_list);
			}
			// while (shell_list->env)
			// {
			// 	printf("{%s}\n", shell_list->env->content);
			// 	shell_list->env = shell_list->env->next;
			// }
			// while (shell_list->cmd->cmd)
			// {
				// 	printf("[%s]\n", shell_list->cmd->cmd[i]);
				// 	i++;
				// }

			// nbr_cmd(shell_list);
			// get_path(shell_list);
			// check_if_access(shell_list);
			// print_node(shell_list, env);
			// execute_commande(shell_list);
			// builtins(shell_list);
		}
		free(input);
	}

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
	// shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	// signal(SIGINT, handle_sigint);  // This assumes you have a signal handler
	// signal(SIGQUIT, SIG_IGN);
	
	// while (1)
	// {
		minishell(shell_list, env);
	// }
	
	// This part would only be reached if the loop is broken
	// ft_malloc(0, FREE);
	return (0);
}
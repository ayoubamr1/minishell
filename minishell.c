#include "minishell.h"

int g_exit_status = 0;

int exite_status ;
static void	ft_null(t_shell *shell)
{
	// shell->env = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
}
void pp(t_token **tok)
{
	t_token *tmp = *tok;
	while (tmp && tmp->content)
	{
		printf("[%s] || type[%d]\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	
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
		// char *str = get_next_line(cc->heredoc);
		// while (cc->heredoc > 0 && str)
		// {
		// 	printf("get=>[%s]", str);
		// 	str = get_next_line(cc->heredoc);
		// }
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
	// int i = 0;
	// if (shell_list->token != NULL)
	// 	clear_token(&shell_list->token);
	// if (shell_list->cmd != NULL)
	// 	clear_cmd(&shell_list->cmd);
	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	shell_list->env = ft_env(shell_list->env, env);
	while (TRUE)
	{
		input = readline("minishell> ");
		if (!input)
			exit(0);
		if (input)
		{
			ft_null(shell_list);
			add_history(input);
			lexer_1(input, &shell_list->token);
			if (syntax_error(&shell_list->token) == TRUE)
			{
				ft_skipe_delimiter(shell_list->token);
				ft_expand(shell_list);
				// pp(&shell_list->token);
				// exit(0);
				shell_list->cmd = ft_malloc(sizeof(t_cmd), MALLOC);
				shell_list->cmd = ft_cmd(shell_list,  &shell_list->token, &shell_list->cmd);
				// print_node(shell_list, env);
				// pp()
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

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell_list;

	// printf("\033[1;32m");
	// printf("███╗   ███╗██╗███╗  ██╗██╗ ██████╗██╗  ██╗███████╗██╗     ██╗     \n");
	// printf("████╗ ████║██║████╗ ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	// printf("██╔████╔██║██║██╔██╗██║██║╚█████╗ ███████║█████╗  ██║     ██║     \n");
	// printf("██║╚██╔╝██║██║██║╚████║██║ ╚═══██╗██╔══██║██╔══╝  ██║     ██║\n");
	// printf("██║ ╚═╝ ██║██║██║ ╚███║██║██████╔╝██║  ██║███████╗███████╗███████╗\n");
	// printf("╚═╝     ╚═╝╚═╝╚═╝  ╚══╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	// printf("\033[0m");
	(void)ac;
	(void)av;
	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	if (isatty(0) == 0)
		exit(0);
signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	
	// while (1)
	// {
	minishell(shell_list, env);
	// }
	
	// This part would only be reached if the loop is broken
	// ft_malloc(0, FREE);
	return (0);
}

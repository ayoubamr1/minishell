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
		// printf("[%s] || type[%d]\n", tmp->content, tmp->type);
		printf("[%s]\n", tmp->content);
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

static void ft_update_token(t_token *tok)
{
	t_token	*tmp;
	t_token	*save;
	char	**spl;
	int		i;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			spl = ft_split(tmp->content, ' ');
			if (spl || spl[0])
			{
				(1) && (i = 1, save = tmp->next);
				tmp->content = spl[0];
				while (spl[i])
				{
					tmp->next = new_token(spl[i++], WORD);
					tmp = tmp->next;
				}
				tmp->next = save;
			}
		}
		tmp = tmp->next;
	}
}

void	minishell(t_shell *shell_list, char **env)
{
	char	*input;

	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	shell_list->env = ft_env(shell_list->env, env);
	// hundle_shlvl(shell_list);
	while (TRUE)
	{
		// reset_signals_inshild();
		input = readline("minishell> ");

		if (!input)
			(printf("exit\n"),exit(0));
		if (input)
		{
			ft_null(shell_list);
			add_history(input);
			lexer_1(input, &shell_list->token);

			if (syntax_error(&shell_list->token) == TRUE)
			{
				// pp(&shell_list->token);
				// exit(0);
				ft_skipe_delimiter(shell_list->token);
				ft_expand(shell_list);
				// ft_update_token(shell_list->token);
				shell_list->cmd = ft_malloc(sizeof(t_cmd), MALLOC);
				shell_list->cmd = ft_cmd(shell_list,  &shell_list->token, &shell_list->cmd);
				// print_node(shell_list, env);
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
	setup_signals();
	// signal(SIGINT, handle_sigint);  // This assumes you have a signal handler
	// signal(SIGQUIT, SIG_IGN);
	
	// while (1)
	// {
	minishell(shell_list, env);
	// }
	
	// This part would only be reached if the loop is broken
	ft_malloc(0, FREE);
	return (0);
}

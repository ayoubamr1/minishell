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
		printf("file[%s] infd[%d] outfd[%d] is_bultins[%d]} fd_status[%d]\n", cc->file, cc->in, cc->out, cc->is_builtin, cc->fd_statuts);
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

	shell_list = ft_malloc(sizeof(t_shell), MALLOC);
	shell_list->env = ft_env(shell_list->env, env);
	while (TRUE)
	{
		input = readline("minishell> ");
		if (!input)
			(exite_status = 0, printf("exit\n"),ft_malloc(0, FREE));
		if (input)
		{
			ft_null(shell_list);
			add_history(input);
			lexer_1(input, &shell_list->token);
			if (syntax_error(&shell_list->token) == TRUE)
			{
				ft_skipe_delimiter(shell_list->token);
				ft_expand(shell_list);
				shell_list->cmd = ft_malloc(sizeof(t_cmd), MALLOC);
				shell_list->cmd = ft_cmd(shell_list,  &shell_list->token, &shell_list->cmd);
				execution(shell_list);
			}
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

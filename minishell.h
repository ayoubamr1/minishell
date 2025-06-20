#ifndef MINISHELL_H
#define MINISHELL_H

#define TRUE  1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h> // signal function
#include <readline/readline.h>
#include <readline/history.h>
#include "tools/gbc.h"
#include <fcntl.h>  // open function 
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
// #include "Get_Next_Line/get_next_line.h"
// #include "leaks.h"
extern int exite_status;
void	handle_sigint(int sig);
typedef enum e_token_type
{
	SI_QUOTE,  //  ''
    WORD,
    PIPE,
    REDIR_IN,   // <
    REDIR_OUT,  // >
    APPEND,     // >>
    HEREDOC,   // << 
	DILIMITER,
	SKIP     
} t_token_type;	
//---------------{ tokenization structure }-----------------
typedef struct s_token
{
    char *content;
    t_token_type type;
	int ex_space_flag;
    int index;
    struct s_token *next;
} t_token;
//---------------{ cmd structure }-----------------
typedef struct s_cmd
{
	char			**cmd; // commend
        // char 			*infile; // file[\] name
	char 			*file; // file name 
	int				in; // file fd
	int				out; //file fd
	int 			fd_statuts;
	int				heredoc_statuts; // 1 if <<
	int				pipe_fd[2];
	int				is_builtin;
	struct s_cmd	*next; // for piped commands
} t_cmd;

//---------------{ env structure }-----------------
typedef struct s_env 
{
	// char			*key;
	// char			*value;
	char			*content;
	int				index;
	int				flag;
	int 			quot;
	struct s_env	*next;
} t_env ;

//---------------{ main structure }-----------------
typedef struct s_shell
{
    char			*content;
    t_token_type 	type;
	t_token 		*token;
	char 		*tmp;
	t_env			*env;
	// char 			*original;
	t_cmd			*cmd;
	char			**path_splited;
	int				nbr_cmd;
	int				fd;
	pid_t			*pid;
	int				saved_fdin;
	int				saved_fdout;
	int exit_status; 
    struct s_shell 	*next;
} t_shell;

void	minishell(t_shell *shell_list, char **env);

//---------------{ tokenization functions }-----------------
int		lexer_1(char *input, t_token **tokens);
void 	lexer_2(t_token **tokens, char *input, int *i, int *index);
void	ft_word(t_token **tokens, char *input, int *i, int *index);
int		syntax_error(t_token **tokens);
// int	skip_quote_block(char *input, int *i, char quote);
//---------------{ cmd functions }-----------------
t_cmd		*ft_cmd(t_shell *shell, t_token **token, t_cmd **cmd_list);
void		handle_heredoc(t_shell *shell, char *delimiter, int fd, t_cmd *node);
t_token		*handle_redir_in(t_cmd *node, t_token *start);
t_token		*handle_redir_out(t_cmd *node, t_token *start);
t_token		*handle_redir_append(t_cmd *node, t_token *start);
t_token 	*store_cmd_node(t_shell *shell, t_cmd *node_to_fill, t_token *start);
t_token 	*handle_token_type(t_cmd *node, t_token *start);
t_token 	*handle_heredoc_token(t_shell *shell, t_cmd *node, t_token *start);
void 		remove_empty_tokens(t_token **head);
void		ft_redirections(t_cmd *head);
int 		get_random_int(void);
void	ft_redirections(t_cmd *head);
void ft_cmd_2(t_shell *shell, t_token *tmp, t_cmd *cmd_tmp);
char	*heredoc_expand(char *str, t_env *env);
//---------------{ expand functions }-----------------
char	*cher_env(char *key, t_env *env, char	quot);
char	*expand_env_var(char *str, int *i, t_env *env, char *res);
char	*ft_dolar(char *str);
char	*strjoin_char(char *str, char c);
char	*join_single_quot(char *str, int *i, char *res);
char	*handle_regular_quotes(char *str, int *i, char *res, char *quot);
int		ft_check_sp(char *str);
char	*handle_var_expand(char *str, int *i, t_shell *shell, char *res);
char	*ft_expand_token(char *str, t_shell *shell);
void	ft_expand(t_shell *shell);
int		is_special_char2(char c);
int 	ft_quote(char c);
t_token	*split_token_ex(t_token *tok, char *str, t_shell *shell);
t_token    *split_to_token_list(t_token *tok, char **spl);
char	**ft_split_space(char *str);
char	*expand_env_var_her(char *str, int *i, t_env *env, char *res);
t_token *token_up(t_token *token);
char	*up_token(char *str, int i);
size_t	ft_count_2d(char **arr);
char	*remove_quotes(char *str);
void	ft_skipe_delimiter(t_token *token);
int	len_n(int n);
char *heredoc_expand(char *str, t_env *env);
void	delimiter_dollar(char *str, char *new, int *i, int *p);
void pp(t_token **tok);/////// remove
void	print_env_list(t_env *lst); /// remove it

void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);

t_cmd	*ft_lstnew_cmd(void);
// int		ft_lstsize_cmd(t_cmd *lst);
void	clear_cmd(t_cmd **lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int	token_str(t_token **token, char *input, int *i, int *index);
// char **ft_join2d(char **s1, char **s2);
//                **  token_tools  **
void	add_token(t_token **lst, char *content, t_token_type type, int index);
t_token	*new_token(char *content, t_token_type type);
char	*substr(char *s, int start, int len);
// void	syntax_error(t_token **tokens);
t_env	*ft_env(t_env *env_list, char **env);

// ---------------general tools -----------------
char	*ft_strdup(const char *s1);	
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *dest, char *src, size_t n);
char	*ft_strcpy(const char *str, char *dest);
// int 	ft_isspace(int c);
// void 	free2d(char **str);
char	**ft_strjoin2d(char **s1, char *s2);
char	**ft_split(const char *str, char c);
int     ft_isalpha(int c);
char	*ft_strstr(char *str, char *to_find);
int     ft_isalnum(int c); /////////////////
char	*ft_strchr(const char *s, int c);
void	ft_putchar(char c); 
int     ft_isdigit(int c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

int	is_special_char(char c);
//           BUILTINS
int		my_export(t_shell *main, char **cmd);
void	ft_plus_equal(t_env *env, char **cmd, int len, char *value, int i);
int	ft_equal(t_shell *main, char **cmd, int len, int i, int flag);
void	add_to_env(t_shell *main, char *new_var);
char	*my_getenv( t_shell *main, char *var_name); // t_shell *main
// void	update_env(t_shell *main, char *var_updated);
void	update_env(t_shell *main, char *key, char *value);
int		my_cd(char **str, t_shell *main);
int		unset_env(t_shell *main, char **var_name);
int		my_echo(char **av, t_cmd *cur);
int		my_pwd(t_shell *main);
int		my_exit(t_shell *main, char **cmd);
// void	builtins(t_shell *main);
void	run_builtins(t_shell *main, char **cmd, t_cmd *cur);
int		is_builtin(char *str);
int 	print_env(t_shell *main);
int		is_valid_var(char **str);
void	environment(t_env *env);
char	*parse_value(char *str, size_t len);
int		search_equal(char **array, int i);
void	add_to_export(t_shell *main, char *cmd);
char	**arrange_array(char **array);

void	handle_sigint(int sig);
void	printf_error(char *var, char* code, int sta);
void	ft_exit(t_shell *main, char *cmd);

//            EXECUTION
void	get_path(t_shell *main);
void	check_if_access(t_shell *main);
void	ft_check_cmd_path(t_cmd *cmd, char **path);
void	ft_creat_pipe(t_cmd *cmd);
void	ft_fork_process(t_shell *main, int i);
void	nbr_cmd(t_shell *main);
void	exec_cmd(t_shell *main);
void	ft_check_child(t_cmd *cmd, int read_fd, int write_fd, t_shell *main);
int		is_builtin(char *str);
char	**env_in_2D(t_shell *main);
void	check_redir(t_shell *main);
void	wait_children(t_shell *main);
void	flag_builtins(t_shell *main);
void	execution(t_shell *main);
void	setup_signals(void);
void	reset_signals_inshild(void);
void	hundle_shlvl(t_shell *main);
void	cleanup(t_shell *main, int status);

char	*get_next_line(int fd);

void	edit_redir(t_shell *main);
void	print_node(t_shell *shell_list, char **env);

#endif

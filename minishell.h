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
// #include "Get_Next_Line/get_next_line.h"
// #include "leaks.h"


typedef enum e_token_type
{
	SI_QUOTE,  //  ''
	// d_quote,  //	""
    STRING,
    WORD,
    PIPE,
    REDIR_IN,   // <
    REDIR_OUT,  // >
    APPEND,     // >>
    HEREDOC,   // << 
    // FILE_IN,   // << 
    // FILE_OUT,   // <<
	VOID     
} t_token_type;
//---------------{ tokenization structure }-----------------
typedef struct s_token
{
    char *content;
    t_token_type type;
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
	int 			heredoc; // 1 if <<
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
	struct s_env	*next;
} t_env ;
//---------------{ main structure }-----------------
typedef struct s_shell
{
    char			*content;
    t_token_type 	type;
	t_token 		*token;
	t_env			*env;
	// char 			*original;
	t_cmd			*cmd;
	char			**path_splited;
	int				nbr_cmd;
	pid_t			*pid;
	int				in_fd;
	int				out_fd;
	int exit_status; 
    struct s_shell 	*next;
} t_shell;

void	minishell(t_shell *shell_list, char **env);

//---------------{ tokenization functions }-----------------
int		lexer_1(char *input, t_token **tokens);
void 	lexer_2(t_token **tokens, char *input, int *i, int *index);
void	ft_word(t_token **tokens, char *input, int *i, int *index);
int		syntax_error(t_token **tokens);
//---------------{ cmd functions }-----------------
void	ft_expand(t_shell	*shell_list);
char *handle_heredoc(t_shell *shell, char *delimiter);



//---------------{ expand functions }-----------------
char	*id_itoa(int n);
char	*remove_quotes(char *str);
// static int	is_special_char(char c);



char	*ft_expand_token(char *str, t_env *env);


void	print_env_list(t_env *lst); /// remove it

void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
// t_cmd	*ft_cmd(t_shell *shell, t_token **token, t_cmd **cmd_list);
t_cmd	*ft_cmd(t_shell *shell, t_token **token, t_cmd **cmd_list, t_env *env);
t_cmd	*ft_lstnew_cmd(void);
// int		ft_lstsize_cmd(t_cmd *lst);
void	clear_cmd(t_cmd **lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int	token_str(t_token **token, char *input, int *i, int *index);
// void	ft_quote(t_token **tokens, char *input, int *i, int *index);

//                **  token_tools  **
void	add_token(t_token **lst, char *content, t_token_type type, int index);
t_token	*new_token(char *content, t_token_type type);
char	*substr(char *s, int start, int len);
void	clear_token(t_token **lst);
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
int 	ft_isspace(int c);
void 	free2d(char **str);
char	**ft_strjoin2d(char **s1, char *s2);
int     ft_isspace(int c);
char	**ft_split(const char *str, char c);
int     ft_isalnum(int c);
void	ft_putchar(char c);
int     ft_isdigit(int c);
int     ft_isalpha(int c);
char	*ft_strchr(const char *s, int c);

int	is_special_char(char c);
//           BUILTINS
void	my_export(t_shell *main, char *var);
void	add_to_env(t_shell *main, char *new_var);
char	*my_getenv( t_shell *main, char *var_name); // t_shell *main
void	update_env(t_shell *main, char *var_updated);
int		my_cd(char **str, t_shell *main);
void	unset_env(t_shell *main, char *var_name);
int		my_echo(char **av, t_cmd *cur);
void	my_pwd(t_shell *main);
// void	builtins(t_shell *main);
void	run_builtins(t_shell *main, char **cmd, t_cmd *cur);
int		is_builtin(char *str);
void 	print_env(t_shell *main);



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


void	edit_redir(t_shell *main);
void	print_node(t_shell *shell_list, char **env);
#endif

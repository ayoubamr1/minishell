#ifndef MINISHELL_H
#define MINISHELL_H

#define TRUE  1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tools/gbc.h"
 #include <fcntl.h> // open function 
// #include "leaks.h"


typedef enum e_token_type
{
	s_quote,  //  ''
	d_quote,  //	""
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
	char			**args; // commend
        // char 			*infile; // file[\] name
	char 			*file; // file name 
	int				in; // file fd
	int				out; //file fd
	// int 			heredoc; // 1 if <<
	struct s_cmd	*next; // for piped commands
} t_cmd;
//---------------{ env structure }-----------------
typedef struct s_env 
{
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
    struct s_shell 	*next;
} t_shell;
//---------------{ tokenization functions }-----------------
void	lexer_1(char *input, t_token **tokens);
void 	lexer_2(t_token **tokens, char *input, int *i, int *index);
void	ft_word(t_token **tokens, char *input, int *i, int *index);
int		syntax_error(t_token **tokens);
//---------------{ cmd functions }-----------------
t_cmd	*ft_cmd(t_token **token, t_cmd **cmd_list);
t_cmd	*ft_lstnew_cmd(void);
// int		ft_lstsize_cmd(t_cmd *lst);
// void	ft_clear_cmd(t_cmd **lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);

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
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, char *src, size_t n);
int 	ft_isspace(int c);
void 	free2d(char **str);
char	**ft_strjoin2d(char **s1, char *s2);

#endif

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

typedef enum e_token_type {
	s_quote,  //  ''
	d_quote,  //	""
    STRING,
    WORD,
    PIPE,
    REDIR_IN,   // <
    REDIR_OUT,  // >
    APPEND,     // >>
    HEREDOC,   // << 
	VOID     
} t_token_type;

typedef struct s_token {
    char *content;
    t_token_type type;
    int index;
	char *original;
	char *in_add;
    struct s_token *next;
} t_token;
// ------------------------------------

//---------------{ tokenization functions }-----------------
void	lexer_1(char *input, t_token **tokens);
int main();
void lexer_2(t_token **tokens, char *input, int *i, int *index);
void	ft_word(t_token **tokens, char *input, int *i, int *index);
void	ft_quote(t_token **tokens, char *input, int *i, int *index);
char	*parse_word_with_quotes(char *input, int *i, t_token **token);
char	*ft_strjoin(char const *s1, char const *s2);
// static char	*join_and_free(char *s1, char *s2);
void	ft_exit(t_token **token);
//                **  token_tools  **
void	add_token(t_token **lst, char *content, t_token_type type, int index);
t_token	*new_token(char *content, t_token_type type);
char	*substr(char *s, int start, int len);
void	ft_lstclear(t_token **lst);

// ---------------general tools -----------------
char	*ft_strdup(const char *s1);

#endif

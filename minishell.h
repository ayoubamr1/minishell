#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

typedef enum e_token_type {
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
    int ind;
	char *original;
    struct s_token *next;
} t_token;


//---------------{ tokenization tools }-----------------

t_token *new_token(char *content, t_token_type type);
void add_token(t_token **lst, char *content, t_token_type type, int index);
char *ft_substr(char *s, int start, int len);
void qoute(t_token **tokens, int *i, char *input, int *index);
void	ft_word(t_token **tokens, int *i, char *input, int *index);
void	lexer_2(t_token **tokens, int *i, char *input, int *index);
void syntax_error(char *input, t_token **tokens);
void pipe_check(t_token **tokens);
// ---------------general tools -----------------
char	*ft_strdup(const char *s1);

#endif
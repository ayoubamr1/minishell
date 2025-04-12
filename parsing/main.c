#include "../minishell.h"


char *get_token(char **str)
{
	char *buf = malloc(4096);
	int i = 0;

	while (**str && isspace(**str))
		(*str)++;

	while (**str && !isspace(**str))
	{
		if (**str == '\'') // single quote
		{
			(*str)++; // skip '
			while (**str && **str != '\'')
				buf[i++] = *((*str)++);
			if (**str == '\'')
				(*str)++;
		}
		else if (**str == '"')
		{
			buf[i++] = *((*str)++);
			while (**str && **str != '"')
				buf[i++] = *((*str)++);
			if (**str == '"')
				buf[i++] = *((*str)++);
		}
		else // normal char
			buf[i++] = *((*str)++);
	}
	buf[i] = '\0';
	return buf;
}



char **tokenize(char *line)
{
	char **tokens = malloc(sizeof(char *) * 100);
	int i = 0;

	while (*line)
	{
		while (*line && isspace(*line))
			line++;
		if (*line)
			tokens[i++] = get_token(&line);
	}
	tokens[i] = NULL;
	return tokens;
}


int main() ////////////// for test
{
    char *input = readline("minishell> ");
 	char **tokens =  tokenize(input);
    int  i = 0;
	while (tokens[i])
    {
        printf("Token: {%s}\n", tokens[i]);
		i++;
    //     (*tokens) = (*tokens)->next;
    }
	printf ("\n---------------------\n");
	// print_tokens(tokens);
	// while (tokens)
	// {
	// printf ("\n1---------------------\n");
	//     // printf("Token: {%s} ==>  Type: %d, index ==> [%d]\n", tokens->content, tokens->type, tokens->index);
	//     printf("Token: {%s}\n", tokens->content);
	//     tokens = tokens->next;
	// }
	// echo 'hello "yool"' | grep hello > file.txt | ls
	// printf ("\n---------------------\n");
}

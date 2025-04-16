#include "../minishell.h"

int main() ////////////// for test
{
	
    // char *input = readline("minishell> ");
	
	// printf ("%s\n", input);
	// free(input);
	char *line;
while (1) {
    line = readline("> ");
    if (!line) break;  // EOF or error
    // if (*line) add_history(line);  // optional
    // process line
    free(line); // ✅ prevent memory leak
}

    return 0;
}


void	lexer_1(t_token **tokens)
{
	printf("{%p} <> {%s}\n", tokens->original, tokens->original);
}

int main() ////////////// for test
{
    char *input = readline("minishell> ");
	if (!input)
		exit(1);
	t_token *tokens = malloc(sizeof(t_token));
	tokens->original = ft_strdup(input);
	tokens = NULL;
	printf("{%p} <> {%s}\n", tokens->original, tokens->original);

    lexer_1(input, &tokens);
    return 0;
}

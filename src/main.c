int	main(int ac, char **av, char **envp)
{
	t_ctx	ctx;
	char	*line;
	t_token	*tokens;
	t_cmd	*ast;

	(void)ac;
	(void)av;
	ctx.envp = envp;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = lexer_tokenize(line);
		ast = parse(tokens);
		if (ast)
			ctx.last_status = executor(&ctx, ast);
		free_cmd(ast);
		token_clear(&tokens);
		free(line);
	}
	return (ctx.last_status);
}
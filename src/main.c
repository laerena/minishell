/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/05/28 12:57:16 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "executor.h"

static int	init_envp(t_ctx *ctx, char **envp);
static void	handle_line(t_ctx *ctx, char *line);
static void	shell_loop(t_ctx *ctx);
static void	cleanup_env(char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	ctx.last_exit_status = 0;
	if (init_envp(&ctx, envp) == 1) //fatal error check, if init_envp fails it will compromise the program
		return (1);
	shell_loop(&ctx);
	cleanup_env(ctx.envp);
	return (0);
}

//dup **envp locally to allow modifications on it
//we need a local cpy of **envp, can t modify the original
static int	init_envp(t_ctx *ctx, char **envp)
{
	size_t	i;

	i = 0;
	while (envp && envp[i])
		i++;
	ctx->envp = ft_calloc((i + 1), sizeof(char *));
	if (!ctx->envp)
		return (1);
	i = 0;
	while (envp && envp[i])
	{
		ctx->envp[i] = ft_strdup(envp[i]);
		if (!ctx->envp[i])
			return (ft_strarr_free(ctx->envp), 1);
		i++;
	}
	return (0);
}

static void	handle_line(t_ctx *ctx, char *line)
{
	t_token	*tokens;
	t_cmd	*ast;

	tokens = lexer_tokenize(line);
	ast = NULL;
	if (tokens)
		ast = parse_expression(tokens);
	if (tokens && !ast)
		ctx->last_exit_status = 1;
	if (ast && expand_ast(ctx, ast) == 0)
		executor(ctx, ast);
	else if (ast)
		ctx->last_exit_status = 1;
	cmd_clear(&ast);
	token_clear(&tokens);
}

static void	shell_loop(t_ctx *ctx)
{
	char	*line;

	handle_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		handle_line(ctx, line);
		free(line);
	}
}

static void	cleanup_env(char **envp)
{
	ft_strarr_free(envp);
}

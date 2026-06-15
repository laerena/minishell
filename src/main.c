/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/06/15 15:43:04 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "executor.h"
#include "init.h"

static void	handle_line(t_ctx *ctx, char *line);
static void	shell_loop(t_ctx *ctx);

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	ctx.last_exit_status = 0;
	ft_bzero(&ctx, sizeof(t_ctx));
	if (init_envp(&ctx, envp) == 1) //fatal error check, if init_envp fails it will compromise the program
		return (1);
	update_shlvl(&ctx);
	shell_loop(&ctx);
	ft_strarr_free(ctx.envp);
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
		{
			write(2, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		handle_line(ctx, line);
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/07/23 18:41:15 by vabisco          ###   ########.fr       */
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
	ft_bzero(&ctx, sizeof(t_ctx));
	if (init(&ctx, envp) != 0) //fatal error check, if init_envp fails it will compromise the program
		return (EXIT_FAILURE);
	shell_loop(&ctx);
	ft_strarr_free(ctx.envp);
	return (0);
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
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		handle_line(ctx, line);
		free(line);
	}
	rl_clear_history();
}

static void	handle_line(t_ctx *ctx, char *line)
{
	t_token	*tokens;
	int		syntax_error;

	syntax_error = 0;
	tokens = lexer_tokenize(line);
	if (!tokens)
		return;
	ctx->ast_head = parse_expression(tokens, &syntax_error);
	token_clear(&tokens);
	if (syntax_error)
		ctx->last_exit_status = 2;
	else if (ctx->ast_head)
		executor(ctx, ctx->ast_head);
	cmd_clear(&ctx->ast_head);
}

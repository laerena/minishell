/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/07/18 15:16:43 by vabisco          ###   ########.fr       */
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

	tokens = lexer_tokenize(line);
	if (tokens)
	{
		ctx->ast_head = parse_expression(tokens);
		if (!ctx->ast_head)
			ctx->last_exit_status = 1;
		token_clear(&tokens);
	}
	executor(ctx, ctx->ast_head);
	cmd_clear(&ctx->ast_head);
}

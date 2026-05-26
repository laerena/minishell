/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 14:33:00 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "executor.h"

static int	init_envp(t_ctx *ctx, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	char	*line;
	t_token	*tokens;
	t_cmd	*ast;

	(void)argc;
	(void)argv;
	if (init_envp(&ctx, envp) == 1)
		return (ft_strarr_free(ctx.envp), 1); // may replace ft_strarr_free by general fclean
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = lexer_tokenize(line);
		ast = parse_expression(tokens);
		if (ast)
		{
			if (expand_ast(&ctx, ast) == 0)
				ctx.last_exit_status = executor(&ctx, ast);
			else
				ctx.last_exit_status = 1;
		}
		cmd_clear(&ast);
		token_clear(&tokens);
		free(line);
	}
	return (ctx.last_exit_status);
}

static int	init_envp(t_ctx *ctx, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	ctx->envp = ft_calloc((i + 1), sizeof(char *));
	if (!ctx->envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		ctx->envp[i] = ft_strdup(envp[i]);
		if (!ctx->envp[i])
			return (1);
		i++;
	}
	ctx->envp[i] = '\0';
	return (0);
}

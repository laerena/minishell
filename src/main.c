/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 14:55:10 by vabisco          ###   ########.fr       */
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
	if (init_envp(&ctx, envp) == 1) //fatal error check, if init_envp fails it will compromise the program
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
		// I think we should not catch the exit code as a LES (last exit status)
		// LES should be setup when a cmd is exec to catch its returns
		// and exit_code should be used to propagate error through nodes
		// I don t need we care about the returns here
		// We should only care about fatal errors returns and then free, exit program otherwise continue
		// proposition:
		// if (ast)
		// {
		// 	expand_ast(&ctx, ast)
		//	executor(&ctx, ast) != 0)
		// }
		if (ast)
		{
			if (expand_ast(&ctx, ast) == 0)
				ctx.last_exit_status = executor(&ctx, ast);
			else
				ctx.last_exit_status = 1;
		}
		//
		cmd_clear(&ast);
		token_clear(&tokens);
		free(line);
	}
	//return (0);
	return (ctx.last_exit_status);
	//
}

//dup **envp locally to allow modifications on it
//we need a local cpy of **envp in our program not the original one
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

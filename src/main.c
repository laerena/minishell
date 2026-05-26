/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/05/25 16:34:20 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "executor.h"

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

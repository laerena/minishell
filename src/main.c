/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:54:55 by leilai            #+#    #+#             */
/*   Updated: 2026/05/21 17:19:11 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "utils.h"
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
			ctx.last_exit_status = executor(&ctx, ast);
		cmd_clear(&ast);
		token_clear(&tokens);
		free(line);
	}
	return (ctx.last_exit_status);
}

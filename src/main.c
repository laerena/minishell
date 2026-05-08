/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:26:50 by leilai            #+#    #+#             */
/*   Updated: 2026/05/02 13:54:50 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "utils.h"

int	main(int ac, char **av, char **envp)
{
	t_ctx	shell;
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	shell.envp = envp;
	shell.last_exit_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = lexer_tokenize(line);
		if (!tokens && *line)
			printf("lexer failed\n");
		else if (check_syntax(tokens))
			printf("syntax error\n");
		else
		{
			print_tokens(tokens);
			cmd = parse_expression(tokens);
			if (!cmd)
				printf("parse failed\n");
			else
			{
				print_ast(cmd);
				cmd_clear(&cmd);
			}
		}
		token_clear(&tokens);
		free(line);
	}
	return (0);
}

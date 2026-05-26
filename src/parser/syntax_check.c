/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:28:58 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 15:16:21 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_binop(t_token_type type)
{
	return (type == T_PIPE
		|| type == T_AND
		|| type == T_OR);
}

/* returns 1 if the token stream starts or ends with an invalid pipe */
static int	check_binop_edges(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (0);
	if (is_binop(tokens->type))
		return (print_syntax_error("unexpected operator"));
	last = tokens;
	while (last->next)
		last = last->next;
	if (is_binop(last->type))
		return (print_syntax_error("unexpected operator"));
	return (0);
}

/* returns 1 if a pipe is followed by another pipe or by nothing */
static int	check_binop_sequence(t_token *tokens)
{
	while (tokens)
	{
		if (is_binop(tokens->type))
		{
			if (!tokens->next || is_binop(tokens->next->type))
				return (print_syntax_error("unexpected operator"));
		}
		tokens = tokens->next;
	}
	return (0);
}

/* returns 1 if a redirection is not followed by a WORD token */
static int	check_redirections(t_token *tokens)
{
	while (tokens)
	{
		if (is_redirection(tokens->type))
		{
			if (!tokens->next || tokens->next->type != T_WORD)
				return (print_syntax_error("expected file"));
		}
		tokens = tokens->next;
	}
	return (0);
}

/* returns 1 on syntax error, 0 if the token stream is valid */
int	check_syntax(t_token *tokens)
{
	if (check_binop_edges(tokens))
		return (1);
	if (check_binop_sequence(tokens))
		return (1);
	if (check_redirections(tokens))
		return (1);
	return (0);
}

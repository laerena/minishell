/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:28:58 by leilai            #+#    #+#             */
/*   Updated: 2026/05/02 14:17:29 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* returns 1 if the token stream starts or ends with an invalid pipe */
static int	check_pipe_edges(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (0);
	if (tokens->type == T_PIPE)
		return (1);
	last = tokens;
	while (last->next)
		last = last->next;
	if (last->type == T_PIPE)
		return (1);
	return (0);
}

/* returns 1 if a pipe is followed by another pipe or by nothing */
static int	check_pipe_sequence(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			if (!tokens->next || tokens->next->type == T_PIPE)
				return (1);
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
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

/* returns 1 on syntax error, 0 if the token stream is valid */
int	check_syntax(t_token *tokens)
{
	if (check_pipe_edges(tokens))
		return (1);
	if (check_pipe_sequence(tokens))
		return (1);
	if (check_redirections(tokens))
		return (1);
	return (0);
}

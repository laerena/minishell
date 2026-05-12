/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_imple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:58:35 by leilai            #+#    #+#             */
/*   Updated: 2026/05/11 20:06:24 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** eg.
** parse_range(start, end)
** 		op = find_last_top_level(start, end, token_type_for_this_level)
** 		if no op
** 			return parse_next_level from [start, end) 
** 						start included, end excluded
** 		else
** 			return <node_type_for_this_level> node
** 				left = parse_same_level(start, op)
** 				right = parse_next_level(op->next, end)
**
** precedence flow:
** 		parse_or()
** 			-> parse_and()
** 				-> parse_pipeline()
** 					-> parse_primary()
*/
static t_cmd	*parse_pipeline(t_token *start, t_token *end)
{
	t_cmd	*left;
	t_cmd	*right;
	t_token	*op;

	op = find_last_top_level(start, end, T_PIPE);
	if (!op)
		return (parse_primary(start, end));
	left = parse_pipeline(start, op);
	right = parse_primary(op->next, end);
	if (!left || !right)
	{
		cmd_clear(&left);
		cmd_clear(&right);
		return (NULL);
	}
	return (new_binop_node(N_PIPE, left, right));
}

static t_cmd	*parse_and(t_token *start, t_token *end)
{
	t_token	*op;
	t_cmd	*left;
	t_cmd	*right;

	op = find_last_top_level(start, end, T_AND);
	if (!op)
		return (parse_pipeline(start, end));
	left = parse_and(start, op);
	right = parse_pipeline(op->next, end);
	if (!left || !right)
		return (cmd_clear(&left), cmd_clear(&right), NULL);
	return (new_binop_node(N_AND, left, right));
}

t_cmd	*parse_or(t_token *start, t_token *end)
{
	t_token	*op;
	t_cmd	*left;
	t_cmd	*right;

	op = find_last_top_level(start, end, T_OR);
	if (!op)
		return (parse_and(start, end));
	left = parse_or(start, op);
	right = parse_and(op->next, end);
	if (!left || !right)
		return (cmd_clear(&left), cmd_clear(&right), NULL);
	return (new_binop_node(N_OR, left, right));
}

/* public parser entry point */
t_cmd	*parse_expression(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_or(tokens, NULL));
}

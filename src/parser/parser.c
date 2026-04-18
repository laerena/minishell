/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:58:35 by leilai            #+#    #+#             */
/*   Updated: 2026/04/18 15:57:38 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** parse_range(start, end)
** 		pipe = find_last_pipe(start_end)
** 		if no pipe
** 			return command node from [start, end) 
**							start included, end excluded
** 		else
** 			return pipe node
** 				parse_range(start, pipe)
** 				parse_range(pipe->next, end)
*/

static t_ast	*parse_command(t_token *start, t_token *end)
{
	t_ast	*node;

	node = ast_new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->av = tokens_to_av(start, end);
	if (!node->av)
		return (free(node), NULL);
	return (node);
}

static t_ast	*parse_pipeline(t_token *start, t_token *end)
{
	t_ast	*node;
	t_ast	*left;
	t_ast	*right;
	t_token	*pipe;

	pipe = find_last_pipe(start, end);
	if (!pipe)
		return (parse_command(start, end));
	node = ast_new_node(NODE_PIPE);
	if (!node)
		return (NULL);
	left = parse_pipeline(start, pipe);
	right = parse_pipeline(pipe->next, end);
	if (!left || !right)
		return (ast_clear(&left), ast_clear(&right), free(node), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_expression(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens, NULL));
}

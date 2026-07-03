/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 09:32:37 by leilai            #+#    #+#             */
/*   Updated: 2026/07/03 14:49:55 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** build a command subtree from tokens in [start, end).
**
** tokens_to_argv creates ["echo", "hi", NULL]
** collect_redirs creates a list of redirections in token order
** if redirs exist, wrap exec node once with N_REDIR
*/
static t_cmd	*parse_command(t_token *start, t_token *end)
{
	char	**argv;
	t_cmd	*cmd;
	t_redir	*redirs;

	argv = tokens_to_argv(start, end);
	if (!argv)
		return (NULL);
	cmd = new_exec_node(argv);
	if (!cmd)
		return (free_split(argv), NULL);
	if (collect_redirs(start, end, &redirs))
	{
		cmd_clear(&cmd);
		return (NULL);
	}
	if (redirs)
		cmd = new_redir_node(cmd, redirs);
	return (cmd);
}

/*
** checks if the whole token range is wrapped by one outer pair of parentheses
*/
static int	is_wrapped_parens(t_token *start, t_token *end)
{
	int		depth;
	t_token	*cur;

	if (!start || start->type != T_LPAREN)
		return (0);
	depth = 0;
	cur = start;
	while (cur && cur != end)
	{
		if (cur->type == T_LPAREN)
			depth++;
		else if (cur->type == T_RPAREN)
			depth--;
		if (depth == 0 && cur->next != end)
			return (0);
		cur = cur->next;
	}
	return (depth == 0);
}

static t_token	*range_last(t_token *start, t_token *end)
{
	t_token	*last;

	last = NULL;
	while (start && start != end)
	{
		last = start;
		start = start->next;
	}
	return (last);
}

t_cmd	*parse_primary(t_token *start, t_token *end)
{
	t_cmd	*inner;
	t_token	*last;

	if (is_wrapped_parens(start, end))
	{
		last = range_last(start, end);
		inner = parse_or(start->next, last);
		if (!inner)
			return (NULL);
		return (new_subshell_node(inner));
	}
	return (parse_command(start, end));
}

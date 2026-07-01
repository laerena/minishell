/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 09:32:37 by leilai            #+#    #+#             */
/*   Updated: 2026/06/29 21:12:36 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*range_last(t_token *start, t_token *end);

/*
** wraps an existing command tree with one redirection node
** take an existing node and put it inside another node as its child
**
** on success: child and file owned by new redirection node
** on failure: both freed here
*/
static t_cmd	*wrap_redir(t_cmd *child, t_token *redir)
{
	char	*file;
	t_cmd	*new_node;

	file = ft_strdup(redir->next->value);
	if (!file)
		return (cmd_clear(&child), NULL);
	new_node = new_redir_node(child, file,
			token_to_redir_type(redir->type));
	if (!new_node)
	{
		free(file);
		cmd_clear(&child);
		return (NULL);
	}
	return (new_node);
}

/*
** build a command subtree from tokens in [start, end).
**
** tokens_to_argv creates ["echo", "hi", NULL]
** new_exec_node() wraps said argv into an N_EXEC node
** scan redirections and wrap
*/
static t_cmd	*parse_command(t_token *start, t_token *end)
{
	char	**argv;
	t_cmd	*cmd;
	t_token	*cur;

	argv = tokens_to_argv(start, end);
	if (!argv)
		return (NULL);
	cmd = new_exec_node(argv);
	if (!cmd)
		return (free_split(argv), NULL);
	cur = range_last(start, end);
	while (cur)
	{
		if (is_redirection(cur->type))
			cmd = wrap_redir(cmd, cur);
		if (!cmd)
			return (NULL);
		if (cur == start)
			break ;
		cur = cur->prev;
	}
	return (cmd);
}

/*
** if range is wrapped by outer parentheses
** 		parse inside
** 		wrap with N_SUBSHELL
** else
**		parse command
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

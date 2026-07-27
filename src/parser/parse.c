/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 09:32:37 by leilai            #+#    #+#             */
/*   Updated: 2026/07/27 by vabisco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*range_last(t_token *start, t_token *end);
static t_token	*find_matching_rparen(t_token *start);
static t_token	*get_subshell_end(t_token *start);
static t_cmd	*parse_exec(t_token *start, t_token *end);
static t_cmd	*parse_redirs(t_cmd *cmd, t_token *start, t_token *end);

/*
** wraps an existing command tree with one redirection node
**
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
** create a simple EXEC node
*/
static t_cmd	*parse_exec(t_token *start, t_token *end)
{
	char	**argv;
	t_cmd	*cmd;

	argv = tokens_to_argv(start, end);
	if (!argv)
		return (NULL);
	cmd = new_exec_node(argv);
	if (!cmd)
	{
		free_split(argv);
		return (NULL);
	}
	return (cmd);
}

/*
** apply redirections around an already parsed command
**
** example:
**
**   (exit) > file
**
** becomes:
**
**   REDIR OUT file
**       SUBSHELL
**           EXEC exit
*/
static t_cmd	*parse_redirs(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*cur;

	cur = range_last(start, end);
	while (cur)
	{
		if (is_redirection(cur->type))
		{
			cmd = wrap_redir(cmd, cur);
			if (!cmd)
				return (NULL);
		}
		if (cur == start)
			break ;
		cur = cur->prev;
	}
	return (cmd);
}

/*
** find the ')' matching the first '('
*/
static t_token	*find_matching_rparen(t_token *start)
{
	t_token	*cur;
	int		depth;

	cur = start;
	depth = 0;
	while (cur)
	{
		if (cur->type == T_LPAREN)
			depth++;
		else if (cur->type == T_RPAREN)
		{
			depth--;
			if (depth == 0)
				return (cur);
		}
		cur = cur->next;
	}
	return (NULL);
}

/*
** return the matching ')' of a subshell start
*/
static t_token	*get_subshell_end(t_token *start)
{
	if (!start || start->type != T_LPAREN)
		return (NULL);
	return (find_matching_rparen(start));
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

/*
** primary command:
**
** (cmd)
**     -> SUBSHELL
**
** cmd
**     -> EXEC
*/
t_cmd	*parse_primary(t_token *start, t_token *end)
{
	t_cmd	*inner;
	t_token	*close;

	close = get_subshell_end(start);
	if (close)
	{
		inner = parse_or(start->next, close);
		if (!inner)
			return (NULL);
		return (new_subshell_node(inner));
	}
	return (parse_exec(start, end));
}

/*
** command = primary + redirections
*/
t_cmd	*parse_command(t_token *start, t_token *end)
{
	t_cmd	*cmd;

	cmd = parse_primary(start, end);
	if (!cmd)
		return (NULL);
	return (parse_redirs(cmd, start, end));
}

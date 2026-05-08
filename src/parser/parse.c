/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 09:32:37 by leilai            #+#    #+#             */
/*   Updated: 2026/05/08 15:52:01 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_cmd	*parse_or(t_token *start, t_token *end)
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

static t_cmd	*parse_primary(t_token *start, t_token *end)
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

/*
** eg.
** parse_range(start, end)
** 		pipe = find_last_pipe(start, end)
** 		if no pipe
** 			return command node from [start, end) 
**							start included, end excluded
** 		else
** 			return pipe node
** 				parse_range(start, pipe)
** 				parse_range(pipe->next, end)
*/
static t_cmd	*parse_pipeline(t_token *start, t_token *end)
{
	t_cmd	*left;
	t_cmd	*right;
	t_token	*op;

	op = find_last_top_level(start, end, T_PIPE);
	if (!op)
		return (parse_primary(start, end));
	left = parse_pipeline(start, pipe);
	right = parse_pipeline(pipe->next, end);
	if (!left || !right)
	{
		cmd_clear(&left);
		cmd_clear(&right);
		return (NULL);
	}
	return (new_binop_node(N_PIPE, left, right));
}

/*
** wraps an existing command tree with one redirection node
** take an existing node and put it inside another node as its child
**
** on success: child and file owned by new redirection node
** on failure: both freed here
*/
static t_cmd	*wrap_redir(t_cmd *child, t_token *redir)
{
	t_cmd	*new_node;
	char	*file;

	file = ft_strdup(redir->next->value);
	if (!file)
		return (cmd_clear(&child), NULL);
	new_node = new_redir_node(child, file,
			token_to_redir_mode(redir->type));
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
** tokens_to_av creates ["echo", "hi", NULL]
** new_exec_node() wraps said av into an N_EXEC node
** scan redirections and wrap
*/
static t_cmd	*parse_command(t_token *start, t_token *end)
{
	char	**av;
	t_cmd	*cmd;
	t_token	*cur;

	av = tokens_to_av(start, end);
	if (!av)
		return (NULL);
	cmd = new_exec_node(av);
	if (!cmd)
		return (free_split(av), NULL);
	cur = start;
	while (cur && cur != end)
	{
		if (is_redirection(cur->type))
		{
			cmd = wrap_redir(cmd, cur);
			if (!cmd)
				return (NULL);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (cmd);
}

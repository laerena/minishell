/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:32:49 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:35:01 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** return the matching ')' of a subshell start
*/
t_token	*get_subshell_end(t_token *start)
{
	if (!start || start->type != T_LPAREN)
		return (NULL);
	return (find_matching_rparen(start));
}

t_token	*range_last(t_token *start, t_token *end)
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
** find the ')' matching the first '('
*/
t_token	*find_matching_rparen(t_token *start)
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

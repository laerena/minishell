/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:29:25 by leilai            #+#    #+#             */
/*   Updated: 2026/05/12 12:51:24 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_type_name(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	if (type == T_AND)
		return ("AND");
	if (type == T_OR)
		return ("OR");
	if (type == T_LPAREN)
		return ("LPAREN");
	if (type == T_RPAREN)
		return ("RPAREN");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type=%s, value=[%s]\n",
			token_type_name(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

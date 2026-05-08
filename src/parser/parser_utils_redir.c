/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 14:11:55 by leilai            #+#    #+#             */
/*   Updated: 2026/05/02 14:19:51 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* check if a token is a redirection operator */
int	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

/* converts token type into redirection mode */
t_redir_mode	token_to_redir_mode(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (R_INPUT);
	if (type == T_REDIR_OUT)
		return (R_OUTPUT);
	if (type == T_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}

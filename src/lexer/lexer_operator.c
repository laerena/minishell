/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:04:19 by leilai            #+#    #+#             */
/*   Updated: 2026/04/16 12:43:34 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* allocate one-char op string and index++ */
static char	*read_single_op(const char *input, int *i, t_token_type *type)
{
	if (input[*i] == '|')
		*type = T_PIPE;
	else if (input[*i] == '<')
		*type = T_REDIR_IN;
	else
		*type = T_REDIR_OUT;
	(*i)++;
	return (ft_substr(input, *i - 1, 1));
}

/* allocate two-char op*/
static char	*read_double_op(const char *input, int *i, t_token_type *type)
{
	if (input[*i] == '<')
		*type = T_HEREDOC;
	else
		*type = T_APPEND;
	*i += 2;
	return (ft_substr(input, *i - 2, 2));
}

char	*read_operator(const char *input, int *i, t_token_type *type)
{
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
		return (read_double_op(input, i, type));
	return (read_single_op(input, i, type));
}
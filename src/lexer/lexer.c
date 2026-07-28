/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:08:19 by leilai            #+#    #+#             */
/*   Updated: 2026/07/28 18:29:56 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Tokenize: break string into meaningful pieces
** - A linked list of tokens
**
** Input string
** - skip spaces
** - if operator, read operator token
** - else read word token
** - append token
** - repeat
*/

static int	handle_token_error(int error)
{
	if (error == LEX_UNCLOSED_QUOTE)
		return (syntax_error("unclosed quote"));
	return (malloc_error());
}

/* create one token from input, append or clean all on fail */
static int	add_next_token(t_token **tokens, const char *input, int *i)
{
	t_token_type	type;
	t_token			*new_node;
	char			*value;
	int				error;

	error = LEX_OK;
	if (is_operator(input[*i]))
		value = read_operator(input, i, &type);
	else
	{
		type = T_WORD;
		value = read_word(input, i, &error);
	}
	if (!value)
		return (handle_token_error(error));
	new_node = token_new(value, type);
	if (!new_node)
		return (free(value), 1);
	token_add_back(tokens, new_node);
	return (0);
}

/* turn input into a linked list of tokens */
t_token	*lexer_tokenize(const char *input, int *lexer_error)
{
	t_token	*tokens;
	int		i;

	*lexer_error = 0;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (add_next_token(&tokens, input, &i))
		{
			*lexer_error = 2;
			token_clear(&tokens);
			return (NULL);
		}
	}
	return (tokens);
}

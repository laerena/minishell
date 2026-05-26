/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:03:33 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 12:09:46 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '&' || c == '(' || c == ')');
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && is_space(input[*i]))
		(*i)++;
}

static int	skip_quote(const char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input [*i] != quote)
		(*i)++;
	if (!input[*i])
		return (1);
	(*i)++;
	return (0);
}

/* allocate and return extracted WORD token string from input */
char	*read_word(const char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (skip_quote(input, i, input[*i]))
				return (NULL);
		}
		else
			(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

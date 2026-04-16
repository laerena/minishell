/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:03:33 by leilai            #+#    #+#             */
/*   Updated: 2026/04/16 12:00:21 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && is_space(input[*i]))
		(*i)++;
}

/* allocate and return extracted WORD token string from input */
char	*read_word(const char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:16:42 by leilai            #+#    #+#             */
/*   Updated: 2026/05/28 13:37:52 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static char	*init_strip(int *do_expand, int *i, char *quote)
{
	*i = 0;
	*quote = 0;
	*do_expand = 1;
	return (ft_strdup(""));
}

char	*strip_heredoc_quotes(char *s, int *do_expand)
{
	char	*res;
	int		i;
	char	quote;

	res = init_strip(do_expand, &i, &quote);
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (is_quote(s[i]) && quote == 0)
		{
			*do_expand = 0;
			quote = s[i++];
		}
		else if (s[i] == quote)
			quote = s[i++];
		else
			res = append_char(res, s[i++]);
		if (!res)
			return (NULL);
	}
	return (res);
}

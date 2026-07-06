/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:34:10 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/06 17:27:43 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	handle_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
	{
		*quote = c;
		return (1);
	}
	if (c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

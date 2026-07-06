/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:16:42 by leilai            #+#    #+#             */
/*   Updated: 2026/07/06 17:36:25 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// heredoc_expand is initialized to 1 when the node is created.
static char	*strip_heredoc_quotes(t_redircmd *n_redir)
{
	char	*res;
	char	quote;
	size_t	i;

	res = ft_strdup("");
	quote = 0;
	i = 0;
	if (!res)
		return (NULL);
	while (n_redir->file[i])
	{
		if (is_quote(n_redir->file[i]) && quote == 0)
		{
			n_redir->heredoc_expand = 0;
			quote = n_redir->file[i];
		}
		else if (n_redir->file[i] == quote)
			quote = 0;
		else
			res = append_char(res, n_redir->file[i]);
		if (!res)
			return (NULL);
		i++;
	}
	return (res);
}

int update_delimiter(t_redircmd *n_redir)
{
	char	*new_delimiter;

	new_delimiter = strip_heredoc_quotes(n_redir);
	if (new_delimiter == NULL)
		return (1);
	free(n_redir->file);
	n_redir->file = new_delimiter;
	return (0);
}

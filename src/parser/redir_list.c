/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:12:32 by leilai            #+#    #+#             */
/*   Updated: 2026/07/03 15:51:01 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*new_redir_item(char *file, t_redir_type type)
{
	t_redir	*redir;

	if (!file)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		free(file);
		return (NULL);
	}
	redir->type = type;
	redir->file = file;
	redir->heredoc_expand = 1;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **list, t_redir *new_item)
{
	t_redir	*cur;

	if (!list || !new_item)
		return ;
	if (!*list)
	{
		*list = new_item;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new_item;
}

static int	append_redir(t_redir **redirs, t_token *redir_token)
{
	char	*file;
	t_redir	*item;

	file = ft_strdup(redir_token->next->value);
	if (!file)
		return (1);
	item = new_redir_item(file, token_to_redir_type(redir_token->type));
	if (!item)
		return (1);
	redir_add_back(redirs, item);
	return (0);
}

int	collect_redirs(t_token *start, t_token *end, t_redir **redirs)
{
	*redirs = NULL;
	while (start && start != end)
	{
		if (is_redirection(start->type))
		{
			if (append_redir(redirs, start))
				return (redir_clear(redirs), 1);
			start = start->next;
		}
		if (start && start != end)
			start = start->next;
	}
	return (0);
}

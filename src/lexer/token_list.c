/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:23:19 by leilai            #+#    #+#             */
/*   Updated: 2026/04/16 15:57:06 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

/* returns the last node of the token list */
static	t_token	*token_last(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

/* append and existing token node to end of list */
void	token_add_back(t_token **lst, t_token *new_node)
{
	t_token	*last;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = token_last(*lst);
	last->next = new_node;
	new_node->prev = last;
}

/*
** frees every token value
** then every token node
** then clears the list pointer
*/
void	token_clear(t_token **lst)
{
	t_token	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = next;
	}
}

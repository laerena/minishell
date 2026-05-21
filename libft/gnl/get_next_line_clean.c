/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_clean.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 19:41:26 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/09 21:47:17 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_full_cleanup(t_gnl_node **hashtable)
{
	t_gnl_node	*node;
	t_gnl_node	*tmp;
	size_t		i;

	i = 0;
	while (i < HASHTABLE_SIZE)
	{
		node = hashtable[i];
		while (node)
		{
			tmp = node->next;
			free(node->stash);
			free(node);
			node = tmp;
		}
		hashtable[i] = NULL;
		i++;
	}
}

void	gnl_cleanup(t_gnl_node **bucket, t_gnl_node *node)
{
	t_gnl_node	*prev;

	if ((*bucket) == node)
		*bucket = node->next;
	else
	{
		prev = *bucket;
		while (prev->next && prev->next != node)
			prev = prev->next;
		if (prev->next != node)
			return ;
		prev->next = node->next;
	}
	free(node->stash);
	free(node);
}

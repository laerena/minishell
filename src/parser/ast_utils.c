/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:51:50 by leilai            #+#    #+#             */
/*   Updated: 2026/04/18 15:51:37 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* initialize */
t_ast	*ast_new_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->av = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

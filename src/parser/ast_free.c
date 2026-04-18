/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:59:38 by leilai            #+#    #+#             */
/*   Updated: 2026/04/16 17:07:50 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_av(char **av)
{
	int	i;

	if (!av)
		return ;
	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

/* free ast recursively and clears the root pointer */
void	ast_clear(t_ast **root)
{
	if (!root || !*root)
		return ;
	ast_clear(&(*root)->left);
	ast_clear(&(*root)->right);
	free_av((*root)->av);
	free(*root);
	*root = NULL;
}

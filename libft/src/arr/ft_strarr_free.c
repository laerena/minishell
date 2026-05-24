/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:50:48 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/11 18:23:34 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarr_free(char **arr)
{
	char	**tmp;

	if (!arr)
		return ;
	tmp = arr;
	while (*tmp)
		free(*tmp++);
	free (arr);
}

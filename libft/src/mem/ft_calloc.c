/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:24:55 by vbisco            #+#    #+#             */
/*   Updated: 2025/10/13 17:42:04 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*tmp;

	tmp = malloc(nelem * elsize);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nelem * elsize);
	return (tmp);
}

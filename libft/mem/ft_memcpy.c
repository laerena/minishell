/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:26:26 by vbisco            #+#    #+#             */
/*   Updated: 2025/10/13 15:10:32 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;

	if (!n)
		return (dest);
	tmpdest = (unsigned char *) dest;
	tmpsrc = (unsigned char *) src;
	while (n-- > 0)
		*tmpdest++ = *tmpsrc++;
	return (dest);
}

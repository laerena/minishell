/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:26:32 by vbisco            #+#    #+#             */
/*   Updated: 2025/10/13 15:17:20 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;

	if (!n)
		return (dest);
	tmpdest = (unsigned char *) dest;
	tmpsrc = (unsigned char *) src;
	if (tmpdest > tmpsrc)
		while (0 < n--)
			tmpdest[n] = tmpsrc[n];
	else if (tmpdest < tmpsrc)
		while (0 < n--)
			*tmpdest++ = *tmpsrc++;
	return (dest);
}

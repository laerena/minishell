/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:27:00 by vbisco            #+#    #+#             */
/*   Updated: 2025/10/13 15:44:56 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	total_len;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	total_len = ft_strlen(src) + dstlen;
	if (size <= dstlen)
		return (ft_strlen(src) + size);
	while (*src && dstlen < size - 1)
		dst[dstlen++] = *src++;
	dst[dstlen] = '\0';
	return (total_len);
}

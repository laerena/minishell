/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:26:48 by vbisco            #+#    #+#             */
/*   Updated: 2025/12/29 15:57:27 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s)
{
	char	*out;
	size_t	len;

	len = ft_strclen(s, '\0');
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s, len);
	out[len] = '\0';
	return (out);
}

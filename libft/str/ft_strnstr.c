/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:27:29 by vbisco            #+#    #+#             */
/*   Updated: 2025/10/13 16:59:00 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t n)
{
	size_t	i;
	size_t	needle_len;

	if (!*needle)
		return ((char *) haystack);
	needle_len = ft_strlen(needle);
	while (n && *haystack && n >= needle_len)
	{
		i = 0;
		while (i < n && haystack[i] && needle[i] && haystack[i] == needle[i])
			i++;
		if (needle[i] == '\0')
			return ((char *) haystack);
		haystack++;
		n--;
	}
	return (NULL);
}

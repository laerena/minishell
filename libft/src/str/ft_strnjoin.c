/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:18:39 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/27 11:51:00 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len1, size_t len2)
{
	char	*out;

	if ((!s1 && !s2) || (!len1 && !len2))
		return (ft_strdup(""));
	if (!s1 || !len1)
		return (ft_strdup(s2));
	if (!s2 || !len2)
		return (ft_strdup(s1));
	out = malloc(len1 + len2 + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s1, len1);
	ft_memcpy(out + len1, s2, len2);
	out[len1 + len2] = '\0';
	return (out);
}

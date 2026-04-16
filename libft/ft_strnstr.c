/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:37:18 by leilai            #+#    #+#             */
/*   Updated: 2025/10/29 15:37:19 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *a, const char *b, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (b[0] == '\0' || b == NULL)
		return ((char *)a);
	while (a[i] != '\0' && i < n)
	{
		if (a[i] == b[j])
		{
			while (a[i + j] == b[j] && i + j < n)
			{
				if (b[j + 1] == '\0')
					return ((char *)a + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}

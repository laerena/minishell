/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:22:20 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/29 13:22:20 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*utoa_convert(unsigned int n, char *str)
{
	if (n > 9)
		str = utoa_convert(n / 10, str);
	*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_utoa(unsigned int n)
{
	size_t			len;
	unsigned int	tmp;
	char			*array;

	len = 0;
	tmp = n;
	if (tmp == 0)
		len++;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	array = ft_calloc(len + 1, sizeof(char));
	if (!array)
		return (NULL);
	utoa_convert(n, array);
	return (array);
}

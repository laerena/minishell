/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:15:28 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/10 12:15:28 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*llitoa_convert(long long int n, char *str)
{
	if (n == LLONG_MIN)
	{
		*str++ = '-';
		str = llitoa_convert(-(n / 10), str);
		n = -(n % 10);
	}
	if (n < 0)
	{
		*str++ = '-';
		n = -n;
	}
	if (n > 9)
		str = llitoa_convert(n / 10, str);
	*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_llitoa(long long int n)
{
	char			*array;
	size_t			len;
	long long int	tmp;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
		len++;
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	array = ft_calloc(len + 1, 1);
	if (!array)
		return (NULL);
	llitoa_convert(n, array);
	return (array);
}

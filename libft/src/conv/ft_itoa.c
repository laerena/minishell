/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:53:50 by vabisco           #+#    #+#             */
/*   Updated: 2025/10/13 18:53:50 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	itoa_size(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		size++;
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*itoa_convert(int n, char *str)
{
	if (n < 0)
	{
		*str++ = '-';
		if (n < -9)
			str = itoa_convert(-(n / 10), str);
		*str++ = -(n % 10) + '0';
		return (str);
	}
	if (n > 9)
		str = itoa_convert(n / 10, str);
	*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*array;

	array = ft_calloc(itoa_size(n) + 1, 1);
	if (!array)
		return (NULL);
	itoa_convert(n, array);
	return (array);
}

// shortest less readable
// static char	*itoa_convert(int n, char *str)
// {
// 	if (n < 0)
// 	{
// 		*str++ = '-';
// 		if (n < -9)
// 			str = itoa_convert(-(n / 10), str);
// 		n = -(n % 10);
// 	}
// 	if (n > 9)
// 		str = itoa_convert(n / 10, str);
// 	*str++ = (n % 10) + '0';
// 	return (str);
// }

// more comprehensible but hard handling edge case
// static char	*itoa_convert(int n, char *str)
// {
// 	if (n == -2147483648)
// 	{
// 		*str++ = '-';
// 		str = itoa_convert(-(n / 10), str);
// 		n = -(n % 10);
// 	}
// 	if (n < 0)
// 	{
// 		*str++ = '-';
// 		n = -n;
// 	}
// 	if (n > 9)
// 		str = itoa_convert(n / 10, str);
// 	*str++ = (n % 10) + '0';
// 	return (str);
// }

// iteration with manual buffer setting
// char	*ft_itoa(int n)
// {
// 	char	buffer[12];
// 	int		i;
// 	int		is_neg;

// 	is_neg = 0;
// 	i = 11;
// 	buffer[i--] = '\0';
// 	if (n == -2147483648)
// 		return (ft_strdup("-2147483648"));
// 	if (n == 0)
// 		return (ft_strdup("0"));
// 	if (n < 0)
// 	{
// 		is_neg = 1;
// 		n = -n;
// 	}
// 	while (n > 0)
// 	{
// 		buffer[i--] = (n % 10) + '0';
// 		n /= 10;
// 	}
// 	if (is_neg)
// 		buffer[i--] = '-';
// 	return (ft_strdup(&buffer[i + 1]));
// }

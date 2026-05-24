/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llutoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:00:09 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/19 15:00:09 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*llutoa_convert(unsigned long long int n, char *str)
{
	if (n > 9)
		str = llutoa_convert(n / 10, str);
	*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_llutoa(unsigned long long int n)
{
	size_t					len;
	unsigned long long int	tmp;
	char					*array;

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
	llutoa_convert(n, array);
	return (array);
}

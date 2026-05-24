/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:43:02 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/24 14:43:02 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*i_to_base(char *array, int n, char *base, int base_len)
{
	if (n == INT_MIN)
	{
		*array++ = '-';
		array = i_to_base(array, -(n / base_len), base, base_len);
		n = -(n % base_len);
	}
	if (n < 0)
	{
		*array++ = '-';
		n = -n;
	}
	if (n > base_len - 1)
		array = i_to_base(array, n / base_len, base, base_len);
	*array++ = base[n % base_len];
	return (array);
}

char	*ft_itoa_base(int n, char *base)
{
	size_t	base_len;
	int		tmp;
	char	*array;
	size_t	len;

	base_len = ft_strlen(base);
	if (!ft_isvalid_base(base, base_len))
		return (NULL);
	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
		len++;
	tmp = n;
	while (tmp)
	{
		tmp /= base_len;
		len++;
	}
	array = ft_calloc(len + 1, sizeof(char));
	if (!array)
		return (NULL);
	i_to_base(array, n, base, base_len);
	return (array);
}

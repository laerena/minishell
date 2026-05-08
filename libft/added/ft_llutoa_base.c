/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llutoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:00:27 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/19 15:00:27 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*llu_to_base(char *array, unsigned long long int n,
	char *base, int base_len)
{
	if (n > (unsigned long long int)base_len - 1)
		array = llu_to_base(array, (n / (unsigned long long int)base_len),
				base, base_len);
	*array++ = base[n % base_len];
	return (array);
}

char	*ft_llutoa_base(unsigned long long int n, char *base)
{
	size_t					base_len;
	unsigned long long int	tmp;
	char					*array;
	size_t					len;

	base_len = ft_strlen(base);
	if (!ft_isvalid_base(base, base_len))
		return (NULL);
	tmp = n;
	len = 0;
	if (tmp == 0)
		len++;
	while (tmp)
	{
		tmp /= base_len;
		len++;
	}
	array = ft_calloc(len + 1, sizeof(char));
	if (!array)
		return (NULL);
	llu_to_base(array, n, base, base_len);
	return (array);
}

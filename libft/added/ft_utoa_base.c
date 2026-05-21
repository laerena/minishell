/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:44:20 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/24 14:44:20 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*u_to_base(char *array, unsigned int n,
	char *base, int base_len)
{
	if (n > (unsigned int)base_len - 1)
		array = u_to_base(array, (n / (unsigned int)base_len),
				base, base_len);
	*array++ = base[n % base_len];
	return (array);
}

char	*ft_utoa_base(unsigned int n, char *base)
{
	size_t			base_len;
	unsigned int	tmp;
	char			*array;
	size_t			len;

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
	u_to_base(array, n, base, base_len);
	return (array);
}

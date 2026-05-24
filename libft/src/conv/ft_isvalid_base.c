/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:38:27 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/29 13:38:27 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isvalid_base(char *base, size_t base_len)
{
	unsigned char	hash[256];
	size_t			i;

	i = 0;
	while (i < 256)
		hash[i++] = 0;
	if (base_len <= 1)
		return (0);
	while (*base)
	{
		if (*base == '+' || *base == '-' || *base == 32
			|| (*base >= 7 && *base <= 13))
			return (0);
		if (!(*base >= 32 && *base <= 126))
			return (0);
		if (hash[(unsigned char)*base])
			return (0);
		else
			hash[(unsigned char)*base] = 1;
		base++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strset_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:40:54 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/19 19:40:54 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strset(char c, size_t size)
{
	char	*str;

	str = malloc(size + 1);
	if (!str)
		return (NULL);
	ft_memset(str, c, size);
	str[size] = '\0';
	return (str);
}

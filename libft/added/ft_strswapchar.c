/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswapchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:12:39 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/27 15:44:02 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strswapchar(char *str, char a, char b)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == a)
			*str = b;
		str++;
	}
}
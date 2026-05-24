/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:24:34 by vbisco            #+#    #+#             */
/*   Updated: 2025/11/24 14:43:10 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *str)
{
	int	sign;
	int	out;

	sign = 1;
	out = 0;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign += 43 - *str++;
	while (*str >= '0' && *str <= '9')
		out = out * 10 + (*str++ - '0');
	return (out * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:44:55 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/24 14:44:55 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoll(char const *str)
{
	long long int	sign;
	long long int	out;

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

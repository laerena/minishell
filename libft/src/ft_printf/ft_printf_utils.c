/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:27:40 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/08 12:31:42 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_int_speci(char speci)
{
	if (speci == 'd' || speci == 'i' || speci == 'u'
		|| speci == 'x' || speci == 'X' )
		return (1);
	return (0);
}

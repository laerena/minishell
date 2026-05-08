/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_perc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:37:17 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/08 11:54:38 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_perc(t_printf_context *ctx)
{
	ctx->arg = ft_strdup("%");
	if (!ctx->arg)
		return (-1);
	ctx->arg_len = 1;
	return (0);
}

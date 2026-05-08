/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:08:47 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/17 14:08:47 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_hex(t_printf_context *ctx, va_list args)
{
	if (ctx->speci == 'x')
		ctx->arg = ft_llutoa_base(
				va_arg(args, unsigned int), "0123456789abcdef");
	else if (ctx->speci == 'X')
		ctx->arg = ft_llutoa_base(
				va_arg(args, unsigned int), "0123456789ABCDEF");
	if (!ctx->arg)
		return (-1);
	ctx->arg_len = ft_strlen(ctx->arg);
	return (0);
}

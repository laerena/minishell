/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:24:19 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/07 17:27:44 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	extract_arg(t_printf_context *ctx, va_list args)
{
	if (ctx->fmt.speci == 'c')
		return (specifier_char(ctx, args));
	else if (ctx->fmt.speci == 's')
		return (specifier_str(ctx, args));
	else if (ctx->fmt.speci == 'd' || ctx->fmt.speci == 'i')
		return (specifier_int(ctx, args));
	else if (ctx->fmt.speci == 'u')
		return (specifier_uint(ctx, args));
	else if (ctx->fmt.speci == 'x' || ctx->fmt.speci == 'X')
		return (specifier_hex(ctx, args));
	else if (ctx->fmt.speci == 'p')
		return (specifier_ptr(ctx, args));
	else if (ctx->fmt.speci == '%')
		return (specifier_perc(ctx));
	return (-1);
}

static int	apply_format(t_printf_context *ctx)
{
	if (format_precision(ctx))
		return (-1);
	if (format_prefix(ctx))
		return (-1);
	if (format_pads(ctx))
		return (-1);
	if (format_assembler(ctx))
		return (-1);
	return (0);
}

int	ft_printf_convert(t_printf_context *ctx, va_list args)
{
	if (extract_arg(ctx, args))
		return (-1);
	ctx->buf.buffer_len = ctx->buf.arg_len;
	if (apply_format(ctx))
		return (-1);
	return (0);
}

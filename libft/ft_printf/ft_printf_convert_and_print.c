/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_and_print.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:24:19 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/10 12:39:13 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	extract_arg(t_printf_context *ctx, va_list args)
{
	if (ctx->speci == 'c')
		return (specifier_char(ctx, args));
	else if (ctx->speci == 's')
		return (specifier_str(ctx, args));
	else if (ctx->speci == 'd' || ctx->speci == 'i')
		return (specifier_int(ctx, args));
	else if (ctx->speci == 'u')
		return (specifier_uint(ctx, args));
	else if (ctx->speci == 'x' || ctx->speci == 'X')
		return (specifier_hex(ctx, args));
	else if (ctx->speci == 'p')
		return (specifier_ptr(ctx, args));
	else if (ctx->speci == '%')
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

int	ft_printf_convert_and_print(t_printf_context *ctx, va_list args,
	int *printed_char)
{
	if (extract_arg(ctx, args))
		return (-1);
	ctx->buffer_len = ctx->arg_len;
	if (apply_format(ctx))
		return (-1);
	write(1, ctx->buffer, ctx->buffer_len);
	*printed_char += (int)ctx->buffer_len;
	return (0);
}

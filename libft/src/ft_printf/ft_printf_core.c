/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:03:39 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/09 21:36:26 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//format order %[flags][width][.precision]([length])specifier
//	flags: -, 0, #,  , +
//	width: minimum field width (e.g., 6 in %6d)
//	.precision: dot followed by number (e.g., .3 in %.3f)
//		nbrs speci to precision
//	specifier: conversion type (c, s, p, d, i, u, x, X, %)

//glibc sheet
// Specifier |   +   |   -   | space |   #   |   0   | Width | Precision
// ----------------------------------------------------------------------
//    %c     |  No   |  Yes  |  No   |  No   |  Yes  |  Yes  |    No
//    %s     |  No   |  Yes  |  No   |  No   |  Yes  |  Yes  |   Yes
//    %p     | Yes*  |  Yes  | Yes*  |  No   |  Yes  |  Yes  |   Yes
//   %d/%i   |  Yes  |  Yes  |  Yes  |  No   |  Yes  |  Yes  |   Yes
//    %u     |  No   |  Yes  |  No   |  No   |  Yes  |  Yes  |   Yes
//  %x/%X    |  No   |  Yes  |  No   |  Yes  |  Yes  |  Yes  |   Yes
//    %%     |  No   |  No   |  No   |  No   |  No   |  No   |    No

// Legend/Notes:
// Yes = flag/field affects output
// No = flag/field is ignored
// Yes* for %p: + and space are printed before the 0x prefix
// For %p, precision pads the hex digits with zeros
// For %%, all flags and width/preci are ignrd on glibc (only % is printed)
// For %x/%X, # adds the 0x/0X prefix
// For %d/%i, + and space print a sign for positive numbers
// For %s, precision limits the number of characters printed

#include "ft_printf.h"

void	freeall(t_printf_context *ctx)
{
	if (ctx->buf.arg)
	{
		free(ctx->buf.arg);
		ctx->buf.arg = NULL;
	}
	if (ctx->buf.prefix)
	{
		free(ctx->buf.prefix);
		ctx->buf.prefix = NULL;
	}
	if (ctx->buf.pad_0)
	{
		free(ctx->buf.pad_0);
		ctx->buf.pad_0 = NULL;
	}
	if (ctx->buf.pad_width)
	{
		free(ctx->buf.pad_width);
		ctx->buf.pad_width = NULL;
	}
	if (ctx->buf.buffer)
	{
		free(ctx->buf.buffer);
		ctx->buf.buffer = NULL;
	}
}

static void	reset_ctx(t_printf_context *ctx)
{
	ctx->fmt.left_justify = 0;
	ctx->fmt.alt_form = 0;
	ctx->fmt.precision = -1;
	ctx->fmt.zero = 0;
	ctx->fmt.width = 0;
	ctx->fmt.speci = '\0';
	ctx->fmt.length = LEN_NONE;
	ctx->fmt.sign = '\0';
	ctx->buf.arg = NULL;
	ctx->buf.prefix = NULL;
	ctx->buf.pad_0 = NULL;
	ctx->buf.pad_width = NULL;
	ctx->buf.buffer = NULL;
	ctx->buf.arg_len = 0;
	ctx->buf.prefix_len = 0;
	ctx->buf.pad_0_len = 0;
	ctx->buf.pad_w_len = 0;
	ctx->buf.buffer_len = 0;
	ctx->alloced = 0;
}

int	process_specifier(t_printf_context *ctx, const char **format, va_list args)
{
	if (ft_printf_parse_format(ctx, format))
		return (freeall(ctx), -1);
	if (ft_printf_convert(ctx, args))
		return (freeall(ctx), -1);
	ctx->alloced = 1;
	return (0);
}

void	process_char(t_printf_context *ctx, const char *format)
{
	ctx->charbuffer[0] = *format;
	ctx->buf.buffer = ctx->charbuffer;
	ctx->buf.buffer_len = 1;
}

int	printf_core(t_printf_context *ctx, const char *format, va_list args)
{
	int	written;

	if (!format)
		return (-1);
	written = 0;
	while (*format)
	{
		reset_ctx(ctx);
		if (*format == '%')
		{
			if (process_specifier(ctx, &format, args) == -1)
				return (-1);
		}
		else
			process_char(ctx, format);
		if (ft_printf_output(ctx))
			return (freeall(ctx), -1);
		written += (unsigned int)ctx->buf.buffer_len;
		if (ctx->alloced)
			freeall(ctx);
		format++;
	}
	return (written);
}

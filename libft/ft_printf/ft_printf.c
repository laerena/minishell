/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:28:17 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/15 16:28:17 by vabisco          ###   ########.fr       */
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
	free(ctx->arg);
	free(ctx->prefix);
	free(ctx->pad_0);
	free(ctx->pad_width);
	free(ctx->buffer);
}

static void	init_ctx(t_printf_context *ctx)
{
	ctx->left_justify = 0;
	ctx->alt_form = 0;
	ctx->precision = -1;
	ctx->zero = 0;
	ctx->width = 0;
	ctx->speci = '\0';
	ctx->length = LEN_NONE;
	ctx->sign = '\0';
	ctx->arg = NULL;
	ctx->prefix = NULL;
	ctx->pad_0 = NULL;
	ctx->pad_width = NULL;
	ctx->buffer = NULL;
	ctx->arg_len = 0;
	ctx->prefix_len = 0;
	ctx->pad_0_len = 0;
	ctx->pad_w_len = 0;
	ctx->buffer_len = 0;
}

static int	printf_core(const char *format, va_list args, int *printed_char)
{
	t_printf_context	ctx;

	while (*format)
	{
		if (*format == '%')
		{
			init_ctx(&ctx);
			if (ft_printf_parse_format(&format, &ctx))
				return (-1);
			if (ft_printf_convert_and_print(&ctx, args, printed_char))
				return (-1);
			freeall(&ctx);
		}
		else
		{
			write(1, format, 1);
			(*printed_char)++;
		}
		format++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_char;

	if (!format)
		return (-1);
	va_start(args, format);
	printed_char = 0;
	if (printf_core(format, args, &printed_char))
		return (-1);
	va_end(args);
	return (printed_char);
}

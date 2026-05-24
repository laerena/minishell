/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_assembler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:45:24 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/29 11:45:24 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// [pad(' ')][prefix(sign/alt)][pad('0')][arg]
// [prefix(sign/alt)][pad('0')][arg][pad(' ')]

static int	format_strnjoin(t_printf_context *ctx, const char *str, size_t len)
{
	char	*tmp;

	tmp = ctx->buf.buffer;
	ctx->buf.buffer = ft_strnjoin(ctx->buf.buffer, str,
			ctx->buf.buffer_len, len);
	free(tmp);
	if (!ctx->buf.buffer)
		return (-1);
	ctx->buf.buffer_len += len;
	return (0);
}

int	format_assembler(t_printf_context *ctx)
{
	ctx->buf.buffer_len = 0;
	if (ctx->buf.pad_width && !ctx->fmt.left_justify)
		if (format_strnjoin(ctx, ctx->buf.pad_width, ctx->buf.pad_w_len))
			return (-1);
	if (ctx->buf.prefix)
		if (format_strnjoin(ctx, ctx->buf.prefix, ctx->buf.prefix_len))
			return (-1);
	if (ctx->buf.pad_0)
		if (format_strnjoin(ctx, ctx->buf.pad_0, ctx->buf.pad_0_len))
			return (-1);
	if (ctx->buf.arg || ctx->fmt.speci == 'c')
		if (format_strnjoin(ctx, ctx->buf.arg, ctx->buf.arg_len))
			return (-1);
	if (ctx->buf.pad_width && ctx->fmt.left_justify)
		if (format_strnjoin(ctx, ctx->buf.pad_width, ctx->buf.pad_w_len))
			return (-1);
	return (0);
}

// add buffer len check before/after assembler
	// int	check_b_len;

	// check_b_len = ctx->buf.buffer_len;
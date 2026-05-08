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

	tmp = ctx->buffer;
	ctx->buffer = ft_strnjoin(ctx->buffer, str, ctx->buffer_len, len);
	free(tmp);
	if (!ctx->buffer)
		return (-1);
	ctx->buffer_len += len;
	return (0);
}

int	format_assembler(t_printf_context *ctx)
{
	ctx->buffer_len = 0;
	if (ctx->pad_width && !ctx->left_justify)
		if (format_strnjoin(ctx, ctx->pad_width, ctx->pad_w_len))
			return (-1);
	if (ctx->prefix)
		if (format_strnjoin(ctx, ctx->prefix, ctx->prefix_len))
			return (-1);
	if (ctx->pad_0)
		if (format_strnjoin(ctx, ctx->pad_0, ctx->pad_0_len))
			return (-1);
	if (ctx->arg || ctx->speci == 'c')
		if (format_strnjoin(ctx, ctx->arg, ctx->arg_len))
			return (-1);
	if (ctx->pad_width && ctx->left_justify)
		if (format_strnjoin(ctx, ctx->pad_width, ctx->pad_w_len))
			return (-1);
	return (0);
}

// add buffer len check before/after assembler
	// int	check_b_len;

	// check_b_len = ctx->buffer_len;
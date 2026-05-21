/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:58:03 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/27 20:58:03 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_sign(t_printf_context *ctx)
{
	char	sign[2];

	sign[0] = ctx->fmt.sign;
	sign[1] = '\0';
	ctx->buf.prefix = ft_strdup(sign);
	if (!ctx->buf.prefix)
		return (-1);
	ctx->buf.prefix_len = 1;
	return (0);
}

static int	format_alt_form(t_printf_context *ctx)
{
	if (ctx->fmt.speci == 'x')
		ctx->buf.prefix = ft_strdup("0x");
	else if (ctx->fmt.speci == 'X')
		ctx->buf.prefix = ft_strdup("0X");
	if (!ctx->buf.prefix)
		return (-1);
	ctx->buf.prefix_len = 2;
	return (0);
}

static int	format_prefix_ptr(t_printf_context *ctx)
{
	if (ctx->fmt.sign == '+')
		ctx->buf.prefix = ft_strdup("+0x");
	else if (ctx->fmt.sign == ' ')
		ctx->buf.prefix = ft_strdup(" 0x");
	else
		ctx->buf.prefix = ft_strdup("0x");
	if (!ctx->buf.prefix)
		return (-1);
	ctx->buf.prefix_len = ft_strlen(ctx->buf.prefix);
	return (0);
}

int	format_prefix(t_printf_context *ctx)
{
	if (ctx->fmt.sign
		&& (ctx->fmt.speci == 'i' || ctx->fmt.speci == 'd'))
	{
		if (format_sign(ctx))
			return (-1);
	}
	else if (ctx->fmt.alt_form
		&& (ctx->fmt.speci == 'x' || ctx->fmt.speci == 'X')
		&& ctx->buf.arg[0] != '0')
	{
		if (format_alt_form(ctx))
			return (-1);
	}
	else if (ctx->fmt.speci == 'p'
		&& ctx->buf.arg && ft_strncmp(ctx->buf.arg, "(nil)", 5))
	{
		if (format_prefix_ptr(ctx))
			return (-1);
	}
	ctx->buf.buffer_len += ctx->buf.prefix_len;
	return (0);
}

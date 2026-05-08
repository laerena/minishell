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

	sign[0] = ctx->sign;
	sign[1] = '\0';
	ctx->prefix = ft_strdup(sign);
	if (!ctx->prefix)
		return (-1);
	ctx->prefix_len = 1;
	return (0);
}

static int	format_alt_form(t_printf_context *ctx)
{
	if (ctx->speci == 'x')
		ctx->prefix = ft_strdup("0x");
	else if (ctx->speci == 'X')
		ctx->prefix = ft_strdup("0X");
	if (!ctx->prefix)
		return (-1);
	ctx->prefix_len = 2;
	return (0);
}

static int	format_prefix_ptr(t_printf_context *ctx)
{
	if (ctx->sign == '+')
		ctx->prefix = ft_strdup("+0x");
	else if (ctx->sign == ' ')
		ctx->prefix = ft_strdup(" 0x");
	else
		ctx->prefix = ft_strdup("0x");
	if (!ctx->prefix)
		return (-1);
	ctx->prefix_len = ft_strlen(ctx->prefix);
	return (0);
}

int	format_prefix(t_printf_context *ctx)
{
	if (ctx->sign && (ctx->speci == 'i' || ctx->speci == 'd'))
	{
		if (format_sign(ctx))
			return (-1);
	}
	else if (ctx->alt_form && (ctx->speci == 'x' || ctx->speci == 'X')
		&& ctx->arg[0] != '0')
	{
		if (format_alt_form(ctx))
			return (-1);
	}
	else if (ctx->speci == 'p' && ctx->arg && ft_strncmp(ctx->arg, "(nil)", 5))
	{
		if (format_prefix_ptr(ctx))
			return (-1);
	}
	ctx->buffer_len += ctx->prefix_len;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_uint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:04:23 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/17 14:04:23 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long int	extract_lluint(t_printf_context *ctx, va_list args)
{
	if (ctx->fmt.length == LEN_LL)
		return (va_arg(args, unsigned long long));
	else if (ctx->fmt.length == LEN_L)
		return (va_arg(args, unsigned long));
	else if (ctx->fmt.length == LEN_Z)
		return (va_arg(args, size_t));
	else
		return (va_arg(args, unsigned int));
}

int	specifier_uint(t_printf_context *ctx, va_list args)
{
	ctx->buf.arg = ft_llutoa(extract_lluint(ctx, args));
	if (!ctx->buf.arg)
		return (-1);
	ctx->buf.arg_len = ft_strlen(ctx->buf.arg);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:58:05 by vabisco           #+#    #+#             */
/*   Updated: 2025/12/10 15:58:05 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long int	extract_llint(t_printf_context *ctx, va_list args)
{
	if (ctx->fmt.length == LEN_LL)
		return (va_arg(args, long long));
	else if (ctx->fmt.length == LEN_L)
		return (va_arg(args, long));
	else if (ctx->fmt.length == LEN_Z)
		return (va_arg(args, ssize_t));
	else
		return (va_arg(args, int));
}

int	specifier_int(t_printf_context *ctx, va_list args)
{
	char			*tmp;

	ctx->buf.arg = ft_llitoa(extract_llint(ctx, args));
	if (!ctx->buf.arg)
		return (-1);
	if ((ctx->buf.arg)[0] == '-')
	{
		ctx->fmt.sign = '-';
		tmp = ctx->buf.arg;
		ctx->buf.arg = ft_strdup(&(ctx->buf.arg)[1]);
		free(tmp);
		if (!ctx->buf.arg)
			return (-1);
	}
	ctx->buf.arg_len = ft_strlen(ctx->buf.arg);
	return (0);
}

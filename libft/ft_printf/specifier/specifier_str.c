/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:39:10 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/17 13:39:10 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_str(t_printf_context *ctx, va_list args)
{
	char	*str;

	if (ctx->fmt.length == LEN_LL || ctx->fmt.length == LEN_Z)
		return (-1);
	else if (ctx->fmt.length == LEN_L)
		return (-42);
	str = va_arg(args, char *);
	if (!str)
	{
		ctx->buf.arg = ft_strdup("(null)");
		if (!ctx->buf.arg)
			return (-1);
		ctx->buf.arg_len = 6;
		return (0);
	}
	ctx->buf.arg = ft_strdup(str);
	if (!ctx->buf.arg)
		return (-1);
	ctx->buf.arg_len = ft_strlen(ctx->buf.arg);
	return (0);
}

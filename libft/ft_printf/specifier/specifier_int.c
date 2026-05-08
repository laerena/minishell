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
	if (ctx->length == LEN_LL)
		return (va_arg(args, long long));
	else if (ctx->length == LEN_L)
		return (va_arg(args, long));
	else if (ctx->length == LEN_Z)
		return (va_arg(args, ssize_t));
	else
		return (va_arg(args, int));
}

int	specifier_int(t_printf_context *ctx, va_list args)
{
	char			*tmp;

	ctx->arg = ft_llitoa(extract_llint(ctx, args));
	if (!ctx->arg)
		return (-1);
	if ((ctx->arg)[0] == '-')
	{
		ctx->sign = '-';
		tmp = ctx->arg;
		ctx->arg = ft_strdup(&(ctx->arg)[1]);
		free(tmp);
		if (!ctx->arg)
			return (-1);
	}
	ctx->arg_len = ft_strlen(ctx->arg);
	return (0);
}

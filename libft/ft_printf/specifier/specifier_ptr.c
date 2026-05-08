/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:19:48 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/18 22:19:48 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_ptr(t_printf_context *ctx, va_list args)
{
	uintptr_t	ptr;

	ptr = va_arg(args, uintptr_t);
	if (!ptr)
	{
		ctx->arg = ft_strdup("(nil)");
		if (!ctx->arg)
			return (-1);
		ctx->arg_len = 5;
		return (0);
	}
	ctx->arg = ft_llutoa_base(ptr, "0123456789abcdef");
	if (!ctx->arg)
		return (-1);
	ctx->arg_len = ft_strlen(ctx->arg);
	return (0);
}

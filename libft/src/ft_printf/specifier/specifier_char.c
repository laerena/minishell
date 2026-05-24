/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:05:19 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/16 17:05:19 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_char(t_printf_context *ctx, va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	ctx->buf.arg = calloc(2, sizeof(char));
	if (!ctx->buf.arg)
		return (-1);
	(ctx->buf.arg)[0] = c;
	ctx->buf.arg_len = 1;
	return (0);
}

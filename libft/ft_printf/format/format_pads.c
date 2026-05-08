/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_padding.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 10:37:05 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/22 10:37:05 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	apply_pads(t_printf_context *ctx)
{
	size_t	pad_len;

	pad_len = (size_t)ctx->width - ctx->buffer_len;
	if (ctx->zero && ctx->precision == -1
		&& !ctx->left_justify
		&& (is_int_speci(ctx->speci) || ctx->speci == 'p'))
	{
		ctx->pad_0 = ft_strset('0', pad_len);
		if (!ctx->pad_0)
			return (-1);
		ctx->pad_0_len = pad_len;
	}
	else
	{
		ctx->pad_width = ft_strset(' ', pad_len);
		if (!ctx->pad_width)
			return (-1);
		ctx->pad_w_len = pad_len;
	}
	ctx->buffer_len += pad_len;
	return (0);
}

int	format_pads(t_printf_context *ctx)
{
	if (ctx->speci == '%')
		return (0);
	if ((size_t)ctx->width < ctx->buffer_len)
		return (0);
	if (apply_pads(ctx))
		return (-1);
	return (0);
}

// int	format_padding(char **buffer, t_format *flags)
// {
// 	char	*tmp;
// 	char	*pad;
// 	size_t	pad_len;

// 	if ((size_t)flags->width <= flags->buffer_len)
// 		return (0);
// 	tmp = *buffer;
// 	pad_len = (size_t)flags->width - flags->buffer_len;
// 	if (flags->left_justify)
// 	{
// 		pad = ft_strset(' ', pad_len);
// 		*buffer = ft_strnjoin(*buffer, pad, flags->buffer_len, pad_len);
// 	}
// 	else if ((flags->zero && flags->precision == -1) &&
// 		(flags->speci != 'c' && flags->speci != 's' && flags->speci != '%'))
// 	{
// 		pad = ft_strset('0', pad_len);
// 		*buffer = ft_strnjoin(pad, *buffer, pad_len, flags->buffer_len);
// 	}
// 	else
// 	{
// 		pad = ft_strset(' ', pad_len);
// 		*buffer = ft_strnjoin(pad, *buffer, pad_len, flags->buffer_len);
// 	}
// 	free(pad);
// 	free(tmp);
// 	if (!*buffer)
// 		return (-1);
// 	flags->buffer_len += pad_len;
// 	return (0);
// }

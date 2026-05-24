/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_precision.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:03:59 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/19 17:03:59 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//trunc happens in format_assembler with ft_strnjoin using arg_len
//so we dont need to alloc new strs to handle formatting
static int	apply_precision(t_printf_context *ctx)
{
	size_t	preci_len;

	preci_len = (size_t)ctx->fmt.precision;
	if (ctx->fmt.speci == 's')
	{
		if (ctx->buf.arg_len > preci_len)
		{
			ctx->buf.arg_len = preci_len;
			ctx->buf.buffer_len = ctx->buf.arg_len;
		}
	}
	else if (ctx->buf.arg_len < preci_len)
	{
		ctx->buf.pad_0 = ft_strset('0', preci_len - ctx->buf.arg_len);
		if (!ctx->buf.pad_0)
			return (-1);
		ctx->buf.pad_0_len = preci_len - ctx->buf.arg_len;
		ctx->buf.buffer_len += ctx->buf.pad_0_len;
	}
	else if (ctx->fmt.precision == 0 && ctx->buf.arg[0] == '0')
	{
		ctx->buf.arg_len = 0;
		ctx->buf.buffer_len = ctx->buf.arg_len;
	}
	return (0);
}

int	format_precision(t_printf_context *ctx)
{
	if (ctx->fmt.precision == -1
		|| ctx->fmt.speci == '%' || ctx->fmt.speci == 'c'
		|| (ctx->fmt.speci == 'p'
			&& ctx->buf.arg && !ft_strncmp(ctx->buf.arg, "(nil)", 5)))
		return (0);
	if (ctx->fmt.speci == 's' && ctx->buf.arg
		&& !ft_strncmp(ctx->buf.arg, "(null)", 6)
		&& (size_t)ctx->fmt.precision < ctx->buf.arg_len)
		ctx->fmt.precision = 0;
	if (apply_precision(ctx))
		return (-1);
	return (0);
}

//###old ones###
// static int	apply_precision(t_printf_context *ctx)
// {
// 	// char	*tmp;
// 	size_t	preci_len;

// 	// tmp = ctx->buf.arg;
// 	preci_len = (size_t)ctx->fmt.precision;
// 	if (ctx->fmt.speci == 's')
// 	{
// 		if (ctx->buf.arg_len > preci_len)
// 		{
// 			// delete malloc? cause of ft_strnjoin using arg_len
// 			// ctx->buf.arg = ft_substr(ctx->buf.arg, 0, preci_len);
// 			// if (!ctx->buf.arg)
// 			// 	return (-1);
// 			ctx->buf.arg_len = preci_len;
// 			// free(tmp);
// 			ctx->buf.buffer_len = ctx->buf.arg_len;
// 		}
// 	}
// 	else if (ctx->buf.arg_len < preci_len)
// 	{
// 		ctx->buf.pad_0 = ft_strset('0', preci_len - ctx->buf.arg_len);
// 		if (!ctx->buf.pad_0)
// 			return (-1);
// 		ctx->buf.pad_0_len = preci_len - ctx->buf.arg_len;
// 		ctx->buf.buffer_len += ctx->buf.pad_0_len;
// 	}
// 	else if (ctx->fmt.precision == 0 && ctx->buf.arg[0] == '0') 
// 	{
// 		// delete malloc? cause of ft_strnjoin using arg_len
// 		// ctx->buf.arg = ft_strdup("");
// 		// if (!ctx->buf.arg)
// 		// 	return (-1);
// 		ctx->buf.arg_len = 0;
// 		ctx->buf.buffer_len = ctx->buf.arg_len;
// 		// free(tmp);
// 	}
// 	return (0);
// }
//###
// static int	apply_precision(char **buffer, t_printf_context *ctx)
// {
// 	char	*tmp;
// 	char	*pad;
// 	size_t	preci_len;

// 	tmp = *buffer;
// 	preci_len = (size_t)ctx->fmt.precision;
// 	if (ctx->fmt.speci == 's' && ctx->buf.buffer_len > preci_len)
// 	{
// 		*buffer = ft_substr(*buffer, 0, preci_len);
// 		free(tmp);
// 	}
// 	else if ((*buffer)[0] == '0' && preci_len == 0)
// 	{
// 		*buffer = ft_strdup("");
// 		free(tmp);
// 	}
// 	else if (ctx->buf.buffer_len < preci_len)
// 	{
// 		pad = ft_strset(preci_len - ctx->buf.buffer_len, '0');
// 		*buffer = ft_strjoin(pad, *buffer);
// 		free(pad);
// 		free(tmp);
// 	}
// 	if (!*buffer)
// 		return (-1);
// 	ctx->buf.buffer_len = ft_strlen(*buffer);
// 	return (0);
// }

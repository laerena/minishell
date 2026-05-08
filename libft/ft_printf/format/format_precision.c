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

	preci_len = (size_t)ctx->precision;
	if (ctx->speci == 's')
	{
		if (ctx->arg_len > preci_len)
		{
			ctx->arg_len = preci_len;
			ctx->buffer_len = ctx->arg_len;
		}
	}
	else if (ctx->arg_len < preci_len)
	{
		ctx->pad_0 = ft_strset('0', preci_len - ctx->arg_len);
		if (!ctx->pad_0)
			return (-1);
		ctx->pad_0_len = preci_len - ctx->arg_len;
		ctx->buffer_len += ctx->pad_0_len;
	}
	else if (ctx->precision == 0 && ctx->arg[0] == '0')
	{
		ctx->arg_len = 0;
		ctx->buffer_len = ctx->arg_len;
	}
	return (0);
}

int	format_precision(t_printf_context *ctx)
{
	if (ctx->precision == -1
		|| ctx->speci == '%' || ctx->speci == 'c'
		|| (ctx->speci == 'p' && ctx->arg && !ft_strncmp(ctx->arg, "(nil)", 5)))
		return (0);
	if (ctx->speci == 's' && ctx->arg && !ft_strncmp(ctx->arg, "(null)", 6)
		&& (size_t)ctx->precision < ctx->arg_len)
		ctx->precision = 0;
	if (apply_precision(ctx))
		return (-1);
	return (0);
}

//###old ones###
// static int	apply_precision(t_printf_context *ctx)
// {
// 	// char	*tmp;
// 	size_t	preci_len;

// 	// tmp = ctx->arg;
// 	preci_len = (size_t)ctx->precision;
// 	if (ctx->speci == 's')
// 	{
// 		if (ctx->arg_len > preci_len)
// 		{
// 			// delete malloc? cause of ft_strnjoin using arg_len
// 			// ctx->arg = ft_substr(ctx->arg, 0, preci_len);
// 			// if (!ctx->arg)
// 			// 	return (-1);
// 			ctx->arg_len = preci_len;
// 			// free(tmp);
// 			ctx->buffer_len = ctx->arg_len;
// 		}
// 	}
// 	else if (ctx->arg_len < preci_len)
// 	{
// 		ctx->pad_0 = ft_strset('0', preci_len - ctx->arg_len);
// 		if (!ctx->pad_0)
// 			return (-1);
// 		ctx->pad_0_len = preci_len - ctx->arg_len;
// 		ctx->buffer_len += ctx->pad_0_len;
// 	}
// 	else if (ctx->precision == 0 && ctx->arg[0] == '0') 
// 	{
// 		// delete malloc? cause of ft_strnjoin using arg_len
// 		// ctx->arg = ft_strdup("");
// 		// if (!ctx->arg)
// 		// 	return (-1);
// 		ctx->arg_len = 0;
// 		ctx->buffer_len = ctx->arg_len;
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
// 	preci_len = (size_t)ctx->precision;
// 	if (ctx->speci == 's' && ctx->buffer_len > preci_len)
// 	{
// 		*buffer = ft_substr(*buffer, 0, preci_len);
// 		free(tmp);
// 	}
// 	else if ((*buffer)[0] == '0' && preci_len == 0)
// 	{
// 		*buffer = ft_strdup("");
// 		free(tmp);
// 	}
// 	else if (ctx->buffer_len < preci_len)
// 	{
// 		pad = ft_strset(preci_len - ctx->buffer_len, '0');
// 		*buffer = ft_strjoin(pad, *buffer);
// 		free(pad);
// 		free(tmp);
// 	}
// 	if (!*buffer)
// 		return (-1);
// 	ctx->buffer_len = ft_strlen(*buffer);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buf_static.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:43:31 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/11 12:55:57 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//print to a buffer (unsafe: no size check)
//prefer using ft_snprintf and ft_vsnprintf
int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	t_printf_context	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.output.mode = PRINTF_BUFFER;
	ctx.output.dynamic = 0;
	ctx.output.buffer = str;
	ctx.output.size = SIZE_MAX;
	return (printf_core(&ctx, format, ap));
}

//print to a buffer with size check (safe)
int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_printf_context	ctx;
	int					ret;

	ft_memset(&ctx, 0, sizeof(ctx));
	ft_memset(str, 0, size);
	ctx.output.mode = PRINTF_BUFFER;
	ctx.output.dynamic = 0;
	ctx.output.buffer = str;
	ctx.output.size = size;
	ret = printf_core(&ctx, format, ap);
	return (ret);
}

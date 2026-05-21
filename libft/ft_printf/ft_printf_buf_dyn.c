/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buf_dyn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:43:47 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/11 13:07:35 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//printf to an allocated buffer
int	ft_asprintf(char **strp, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vasprintf(strp, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_vasprintf(char **strp, const char *format, va_list ap)
{
	t_printf_context	ctx;
	int					ret;

	ft_memset(&ctx, 0, sizeof(ctx));
	*strp = NULL;
	ctx.output.mode = PRINTF_BUFFER;
	ctx.output.dynamic = 1;
	ctx.output.size = 0;
	ctx.output.buffer = NULL;
	ret = printf_core(&ctx, format, ap);
	if (ctx.output.buffer == NULL)
	{
		*strp = NULL;
		return (-1);
	}
	*strp = ctx.output.buffer;
	return (ret);
}

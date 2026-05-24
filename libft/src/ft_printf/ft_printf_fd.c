/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:40:53 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/09 21:44:31 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//print to fd
int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start (ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_printf_context	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.output.mode = PRINTF_FD;
	ctx.output.fd = fd;
	return (printf_core(&ctx, format, ap));
}

//print to stderr
int	ft_eprintf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_veprintf(format, ap);
	va_end(ap);
	return (ret);
}

int	ft_veprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(STDERR_FILENO, format, ap));
}

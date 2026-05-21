/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:46:46 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/11 13:14:25 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_buffers_output(t_printf_output *out,
	const char *buffer, size_t buffer_len)
{
	char	*new_buffer;
	size_t	new_size;

	if (out->size == 0 || out->pos + buffer_len > out->size - 1)
	{
		if (out->dynamic == 0)
			buffer_len = out->size - out->pos - 1;
		else if (out->dynamic == 1)
		{
			new_size = out->size * 2 + buffer_len + 1;
			new_buffer = ft_realloc(out->buffer, out->pos, new_size);
			if (!new_buffer)
				return (-1);
			out->buffer = new_buffer;
			out->size = new_size;
		}
	}
	ft_memcpy(out->buffer + out->pos, buffer, buffer_len);
	out->pos += buffer_len;
	if (out->pos >= out->size)
		out->buffer[out->size] = '\0';
	else
		out->buffer[out->pos] = '\0';
	return (0);
}

int	ft_printf_output(t_printf_context *ctx)
{
	t_printf_output	*out;
	char			*buffer;
	size_t			buffer_len;

	out = &ctx->output;
	buffer = ctx->buf.buffer;
	buffer_len = ctx->buf.buffer_len;
	if (out->mode == PRINTF_FD)
		write(out->fd, buffer, buffer_len);
	else if (out->mode == PRINTF_BUFFER)
		if (handle_buffers_output(out, buffer, buffer_len) == -1)
			return (-1);
	return (0);
}

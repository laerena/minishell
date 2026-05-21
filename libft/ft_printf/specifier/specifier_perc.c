/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_perc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:37:17 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/09 21:32:16 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_perc(t_printf_context *ctx)
{
	ctx->buf.arg = ft_strdup("%");
	if (!ctx->buf.arg)
		return (-1);
	ctx->buf.arg_len = 1;
	return (0);
}

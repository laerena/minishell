/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:50:52 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:11:01 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_exit(t_ctx *ctx)
{
	ft_printf("EXITING\n");
	exit(ctx->last_exit_status);
}

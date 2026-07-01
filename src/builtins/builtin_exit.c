/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:50:52 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/19 15:15:42 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_exit(t_ctx *ctx)
{
	if (write(2, "exit\n", 5) == -1)
		ctx->last_exit_status = 1;
	else
		ctx->last_exit_status = 0;
	exit(ctx->last_exit_status);
}

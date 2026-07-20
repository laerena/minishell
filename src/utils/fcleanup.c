/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcleanup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:28:25 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 12:54:59 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"

void	ctx_cleanup(t_ctx *ctx)
{
	if (ctx->ast_head)
		cmd_clear(&ctx->ast_head);
	if (ctx->envp)
		ft_strarr_free(ctx->envp);
	rl_clear_history();
}

void	exit_clean(t_ctx *ctx, int exit_code)
{
	ctx_cleanup(ctx);
	exit(exit_code);
}

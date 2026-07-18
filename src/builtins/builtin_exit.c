/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:50:52 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/18 16:01:46 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "parser.h"

void	builtin_exit(t_ctx *ctx)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	cmd_clear(&ctx->ast_head);
	ft_strarr_free(ctx->envp);
	rl_clear_history();
	ctx->last_exit_status = 0;
	exit(ctx->last_exit_status);
}

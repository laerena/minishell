/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_control_flow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 13:11:17 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/21 17:35:49 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	run_and(t_ctx *ctx, t_cmd *ast_node)
{
	int		exit_code;
	t_cmd	*left;
	t_cmd	*right;

	left = ast_node->u_cmd.binop.left;
	right = ast_node->u_cmd.binop.right;
	exit_code = executor(ctx, left);
	if (exit_code != 0)
		return (exit_code);
	exit_code = executor(ctx, right);
	return (exit_code);
}

int	run_or(t_ctx *ctx, t_cmd *ast_node)
{
	int		exit_code;
	t_cmd	*left;
	t_cmd	*right;

	left = ast_node->u_cmd.binop.left;
	right = ast_node->u_cmd.binop.right;
	exit_code = executor(ctx, left);
	if (exit_code == 0)
		return (0);
	exit_code = executor(ctx, right);
	return (exit_code);
}

int	run_subshell(t_ctx *ctx, t_cmd *ast_node)
{
	int	exit_code;

	exit_code = run_in_child(ctx, ast_node->u_cmd.subshell.child);
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

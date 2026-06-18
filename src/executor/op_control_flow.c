/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_control_flow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 13:11:17 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/16 13:50:31 by vabisco          ###   ########.fr       */
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

//create a child to run the next ast_node inside and wait for it
//return the exit code (int: 0-255)
int	run_subshell(t_ctx *ctx, t_cmd *ast_node)
{
	pid_t	child_pid;
	int		status;
	int		exit_code;

	child_pid = fork();
	if (child_pid == 0)
	{
		signals_reset();
		exit(executor(ctx, ast_node->u_cmd.subshell.child));
	}
	waitpid(child_pid, &status, 0);
	exit_code = convert_status_to_exitcode(status);
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

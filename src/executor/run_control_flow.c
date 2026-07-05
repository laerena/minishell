/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_control_flow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 13:11:17 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/05 13:53:01 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// run '&&' operator
int	run_and(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	int		exit_code;
	t_cmd	*left;
	t_cmd	*right;

	left = ast_node->u_cmd.binop.left;
	right = ast_node->u_cmd.binop.right;
	exit_code = run_ast(ctx, left, no_fork);
	if (exit_code != 0)
		return (exit_code);
	exit_code = run_ast(ctx, right, no_fork);
	return (exit_code);
}

// run '||' operator
int	run_or(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	int		exit_code;
	t_cmd	*left;
	t_cmd	*right;

	left = ast_node->u_cmd.binop.left;
	right = ast_node->u_cmd.binop.right;
	exit_code = run_ast(ctx, left, no_fork);
	if (exit_code == 0)
		return (0);
	exit_code = run_ast(ctx, right, no_fork);
	return (exit_code);
}

//create a child to run the next ast_node inside and wait for it
//return the exit code (int: 0-255)
int	run_subshell(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	return (fork_and_run_in(ctx, ast_node->u_cmd.subshell.child, run_ast, no_fork));
}

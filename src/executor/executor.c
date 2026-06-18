/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:32:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/18 12:12:36 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "expander.h"

static int	run_node(t_ctx *ctx, t_cmd *ast_node);
static int	run_cmd(t_ctx *ctx, t_cmd *ast_node);

// check if the next node is a builtin cmd then run it directly
// or if not run_in_child the next node
// update last_exit_status
// return exit code (int: 0-255)

//run_builtin_or_child became executor, a dispatcher,
//and main entry point of the executor part of minishell
//entry point of all ast_node execution


//wrapper : entry point of executor dir
//start the execution of the ast
int	executor(t_ctx *ctx, t_cmd *ast_node)
{
	return (run_node(ctx, ast_node));
}

static int	run_node(t_ctx *ctx, t_cmd *ast_node)
{
	if (!ast_node)
		return (1);
	if (ast_node->type == N_EXEC)
		return (run_cmd(ctx, ast_node));
	else if (ast_node->type == N_PIPE)
		return (run_pipe(ctx, ast_node));
	else if (ast_node->type == N_REDIR)
		return (run_redir(ctx, ast_node));
	else if (ast_node->type == N_AND)
		return (run_and(ctx, ast_node));
	else if (ast_node->type == N_OR)
		return (run_or(ctx, ast_node));
	else if (ast_node->type == N_SUBSHELL)
		return (run_subshell(ctx, ast_node));
	else
	{
		ft_eprintf("wrong node->type: %i\n", ast_node->type);
		//fcleanup(ctx), may handle fcleanup in the main;
		ctx->last_exit_status = 127;
		return (127);
	}
}

static int	run_cmd(t_ctx *ctx, t_cmd *ast_node)
{
	expand_ast(ctx, ast_node);
	if (ast_node->u_cmd.exec.builtin)
		return (run_builtin(ctx, ast_node));
	else
		return (run_execve_wrapper(ctx, ast_node));
}

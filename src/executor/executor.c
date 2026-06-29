/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:32:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/18 13:47:47 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "expander.h"

static int	run_node(t_ctx *ctx, t_cmd *ast_node);
static int	run_cmd(t_ctx *ctx, t_cmd *ast_node);
// static int	restore_fds(t_ctx *ctx);

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
	int	ret;

	if (expand_ast(ctx, ast_node))
		return (1);
	ret = 0;
	if (ast_node->u_cmd.exec.builtin)
	{
		ret = run_builtin(ctx, ast_node);
	}
	else
		ret = run_execve_wrapper(ctx, ast_node);
	return (ret);
}

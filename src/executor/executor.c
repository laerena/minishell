/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:32:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/01 14:18:59 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "expander.h"

static int	run_node(t_ctx *ctx, t_cmd *ast_node, int no_fork);

//wrapper : entry point
//start the recursive execution of the ast
int	executor(t_ctx *ctx, t_cmd *ast_node)
{
	int	no_fork;

	no_fork = 0;
	return (run_ast(ctx, ast_node, no_fork));
}

int	run_ast(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	if (!ast_node)
		return (1);
	if (ast_node->type == N_EXEC)
		return (run_node(ctx, ast_node, no_fork));
	else if (ast_node->type == N_PIPE)
		return (run_pipe(ctx, ast_node, no_fork));
	else if (ast_node->type == N_REDIR)
		return (run_redir(ctx, ast_node, no_fork));
	else if (ast_node->type == N_AND)
		return (run_and(ctx, ast_node, no_fork));
	else if (ast_node->type == N_OR)
		return (run_or(ctx, ast_node, no_fork));
	else if (ast_node->type == N_SUBSHELL)
		return (run_subshell(ctx, ast_node, no_fork));
	else
	{
		ft_eprintf("wrong node->type: %i\n", ast_node->type);
		//fcleanup(ctx), may handle fcleanup in the main;
		ctx->last_exit_status = 127;
		return (127);
	}
}

static int	run_node(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	t_execmd	*cmd;

	cmd = &ast_node->u_cmd.exec;
	// what exactly does the expander ? is it usefull to expand redir pipe.. ?
	// if (expand_ast(ctx, ast_node))
	// 	return (1);
	// may expand wildcards here isntead of inside builtin and execve wrap
	if (cmd->builtin != BUILTIN_NONE)
		return (run_builtin(ctx, cmd));
	else if(no_fork == 1)
		return(run_execve(ctx, cmd));
	//could simplify by just fork and call execve here instead of run_ast in fork_and_run
	return (fork_and_run(ctx, ast_node));
}

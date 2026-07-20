/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:49:17 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 15:40:44 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "error.h"

static pid_t	fork_left_child(t_ctx *ctx, int *pipefd, t_cmd *ast_node);
static pid_t	fork_right_child(t_ctx *ctx, int *pipefd, t_cmd *ast_node);
static int		pipe_child_error(t_ctx *ctx, int *pipefd);
static void		close_pipefd(int *pipefd);

int	run_pipe(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	(void)no_fork;
	if (pipe(pipefd) == -1)
		return (fail(ctx, 1, "pipe failed"));
	status = 0;
	left_pid = fork_left_child(ctx, pipefd, ast_node);
	if (left_pid == -1)
		return (pipe_child_error(ctx, pipefd));
	right_pid = fork_right_child(ctx, pipefd, ast_node);
	if (right_pid == -1)
	{
		waitpid(left_pid, NULL, 0);
		return (pipe_child_error(ctx, pipefd));
	}
	close_pipefd(pipefd);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	return (exit_code_from_status(ctx, status));
}

static pid_t	fork_left_child(t_ctx *ctx, int *pipefd, t_cmd *ast_node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signals_reset();
		if (my_dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			close_pipefd(pipefd);
			ctx_cleanup(ctx);
			exit(1);
		}
		close_pipefd(pipefd);
		status = run_ast(ctx, ast_node->u_cmd.binop.left, 1);
		ctx_cleanup(ctx);
		exit(status);
	}
	return (pid);
}

static pid_t	fork_right_child(t_ctx *ctx, int *pipefd, t_cmd *ast_node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signals_reset();
		if (my_dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			close_pipefd(pipefd);
			ctx_cleanup(ctx);
			exit (1);
		}
		close_pipefd(pipefd);
		status = run_ast(ctx, ast_node->u_cmd.binop.right, 1);
		ctx_cleanup(ctx);
		exit(status);
	}
	return (pid);
}

static int	pipe_child_error(t_ctx *ctx, int *pipefd)
{
	close_pipefd(pipefd);
	ctx->last_exit_status = 1;
	return (1);
}

static void	close_pipefd(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

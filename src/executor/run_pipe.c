/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:49:17 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/03 15:30:36 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

// static int			my_dup2(int oldfd, int newfd);
static void	handle_left_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node);
static void	handle_right_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node);

int	run_pipe(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	(void)no_fork;
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		return (ctx->last_exit_status = 1, 1);
	}
	status = 0;
	left_pid = fork();
	if (left_pid == 0)
		handle_left_pid(ctx, pipefd, ast_node);
	right_pid = fork();
	if (right_pid == 0)
		handle_right_pid(ctx, pipefd, ast_node);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	return (exit_code_from_status(ctx, status));
}

static void	handle_left_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node)
{
	int	child_ctx;

	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	child_ctx = 1;
	exit(run_ast(ctx, ast_node->u_cmd.binop.left, child_ctx));
}

static void	handle_right_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node)
{
	int	child_ctx;

	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	child_ctx = 1;
	exit(run_ast(ctx, ast_node->u_cmd.binop.right, child_ctx));
}

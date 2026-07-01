/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   helper.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vabisco <vabisco@student.42lausanne.ch>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/05/03 13:28:16 by vabisco		   #+#	#+#			 */
/*   Updated: 2026/06/20 17:01:48 by vabisco		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "executor.h"

//helper ft for parent process that fork into child (/doc/signal_exit_status.txt)
//convert the raw exit status from waitpid into an exit code
//return exit code (int: 0-255)
int	exit_code_from_status(t_ctx *ctx, int status)
{
	int	exit_code;

	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

// restore fds to their original state
int	restore_fds(t_ctx *ctx)
{
	if (ctx->saved_fds.save_stdin >= 0)
	{
		if (dup2(ctx->saved_fds.save_stdin, STDIN_FILENO) == -1)
			return (1);
		close(ctx->saved_fds.save_stdin);
		ctx->saved_fds.save_stdin = -1;
	}
	if (ctx->saved_fds.save_stdout >= 0)
	{
		if (dup2(ctx->saved_fds.save_stdout, STDOUT_FILENO) == -1)
			return (1);
		close(ctx->saved_fds.save_stdout);
		ctx->saved_fds.save_stdout = -1;
	}
	if (ctx->saved_fds.save_stderr >= 0)
	{
		if (dup2(ctx->saved_fds.save_stderr, STDERR_FILENO) == -1)
			return (1);
		close(ctx->saved_fds.save_stderr);
		ctx->saved_fds.save_stderr = -1;
	}
	return (0);
}

int	fork_and_run(t_ctx *ctx, t_cmd *ast_node)
{
	pid_t	child_pid;
	int		child_ctx;
	int		status;

	child_pid = fork();
	if (child_pid == 0)
	{
		signals_reset();
		child_ctx = 1;
		exit(run_ast(ctx, ast_node, child_ctx));
	}
	waitpid(child_pid, &status, 0);
	return (exit_code_from_status(ctx, status));
}

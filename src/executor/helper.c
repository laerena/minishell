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

int	fork_and_run_in(t_ctx *ctx, t_cmd *ast_node, t_fork_and_run_in run_ft, int no_fork)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == -1)
		return (ctx->last_exit_status = 1, 1);
	if (child_pid == 0)
	{
		signals_reset();
		no_fork = 1;
		exit(run_ft(ctx, ast_node, no_fork));
	}
	signals_ignore();
	waitpid(child_pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	handle_signals();
	return (exit_code_from_status(ctx, status));
}

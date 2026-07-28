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
#include "utils.h"
#include "expander.h"

//helper ft for parent process that fork into child
//(/doc/signal_exit_status.txt)
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

int	fork_and_run_in(t_ctx *ctx, t_cmd *ast_node,
		t_fork_and_run_ft run_ft, int no_fork)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == -1)
		return (ctx->last_exit_status = 1, 1);
	if (child_pid == 0)
		run_child(ctx, ast_node, run_ft, no_fork);
	signals_ignore();
	waitpid(child_pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	handle_signals();
	return (exit_code_from_status(ctx, status));
}

void	run_child(t_ctx *ctx, t_cmd *node,
			t_fork_and_run_ft run_ft, int no_fork)
{
	int	status;

	signals_reset();
	ctx->is_main_shell = 0;
	status = run_ft(ctx, node, no_fork);
	ctx_cleanup(ctx);
	exit(status);
}

char	*remove_quotes(char *s)
{
	char	*res;
	char	quote;
	size_t	i;

	if (!s)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	quote = 0;
	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]) && quote == 0)
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		else
			res = append_char(res, s[i]);
		if (!res)
			return (NULL);
		i++;
	}
	return (res);
}

//Parse the ast to clear heredoc s fds
void	close_heredoc_fds(t_cmd *node)
{
	if (!node)
		return ;
	if (node->type == N_REDIR)
	{
		if (node->u_cmd.redir.type == R_HEREDOC
			&& node->u_cmd.redir.heredoc_fd >= 0)
		{
			close(node->u_cmd.redir.heredoc_fd);
			node->u_cmd.redir.heredoc_fd = -1;
		}
		close_heredoc_fds(node->u_cmd.redir.cmd);
	}
	else if (node->type == N_PIPE
		|| node->type == N_AND
		|| node->type == N_OR)
	{
		close_heredoc_fds(node->u_cmd.binop.left);
		close_heredoc_fds(node->u_cmd.binop.right);
	}
	else if (node->type == N_SUBSHELL)
		close_heredoc_fds(node->u_cmd.subshell.child);
}

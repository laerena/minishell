/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:09:05 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:15:52 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

int	heredoc_abort(t_ctx *ctx, int pipefd[2],
	int saved_stdin, int status)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	handle_signals();
	g_signal = 0;
	ctx->last_exit_status = status;
	return (-1);
}

int	restore_heredoc(t_ctx *ctx, int saved_stdin, int pipefd[2])
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		close(saved_stdin);
		close(pipefd[0]);
		close(pipefd[1]);
		ctx->last_exit_status = 1;
		return (-1);
	}
	close(saved_stdin);
	handle_signals();
	g_signal = 0;
	close(pipefd[1]);
	return (pipefd[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:13:11 by leilai            #+#    #+#             */
/*   Updated: 2026/06/30 16:05:27 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

static int	is_limiter(char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	return (ft_strncmp(line, limiter, len + 1) == 0);
}

static int	write_heredoc_line(t_ctx *ctx, int fd, char *line, int do_expand)
{
	char	*expanded;

	expanded = line;
	if (do_expand)
	{
		expanded = expand_str(ctx, line);
		if (!expanded)
			return (1);
	}
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	if (do_expand)
		free(expanded);
	return (0);
}

static int	fill_heredoc(t_ctx *ctx, int fd, t_cmd *ast_node)
{
	char	*line;
	int		ret;

	ret = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_limiter(line, ast_node->u_cmd.redir.file))
		{
			free(line);
			break ;
		}
		ret = write_heredoc_line(ctx, fd, line,
				ast_node->u_cmd.redir.heredoc_expand);
		free(line);
		if (ret)
			break ;
	}
	return (ret);
}

static int	heredoc_to_stdin(t_ctx *ctx, int pipefd[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		close(pipefd[0]);
		ctx->last_exit_status = 1;
		return (1);
	}
	close(pipefd[0]);
	return (0);
}

int	run_heredoc(t_ctx *ctx, t_cmd *ast_node)
{
	int	pipefd[2];
	int	exit_code;

	if (pipe(pipefd) < 0)
		return (ctx->last_exit_status = 1, 1);
	g_signal = 0;
	if (dup2(ctx->saved_fds.save_stdin, STDIN_FILENO) == -1)
		return (close(pipefd[0]), close(pipefd[1]),
			ctx->last_exit_status = 1, 1);
	handle_heredoc_signals();
	if (fill_heredoc(ctx, pipefd[1], ast_node) || g_signal == SIGINT)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(ctx->saved_fds.save_stdin, STDIN_FILENO);
		handle_signals();
		return (ctx->last_exit_status = 130, 130);
	}
	handle_signals();
	if (heredoc_to_stdin(ctx, pipefd))
		return (1);
	exit_code = executor(ctx, ast_node->u_cmd.redir.cmd);
	if (dup2(ctx->saved_fds.save_stdin, STDIN_FILENO) == -1)
		return (ctx->last_exit_status = 1, 1);
	return (exit_code);
}

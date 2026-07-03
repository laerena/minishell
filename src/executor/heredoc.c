/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:13:11 by leilai            #+#    #+#             */
/*   Updated: 2026/07/03 14:56:25 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "utils.h"
#include "error.h"

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

static int	fill_heredoc(t_ctx *ctx, int fd, t_redir *redir)
{
	char	*line;
	int		ret;

	ret = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_limiter(line, redir->file))
		{
			free(line);
			break ;
		}
		ret = write_heredoc_line(ctx, fd, line, redir->heredoc_expand);
		free(line);
		if (ret)
			break ;
	}
	return (ret);
}

static int	heredoc_abort(t_ctx *ctx, int pipefd[2],
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
	ctx->last_exit_status = status;
	return (-1);
}

int	create_heredoc(t_ctx *ctx, t_redir *redir)
{
	int	pipefd[2];
	int	saved_stdin;

	if (pipe(pipefd) < 0)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	g_signal = 0;
	handle_heredoc_signals();
	if (fill_heredoc(ctx, pipefd[1], redir))
		return (heredoc_abort(ctx, pipefd, saved_stdin, 1));
	if (g_signal == SIGINT)
		return (heredoc_abort(ctx, pipefd, saved_stdin, 130));
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	handle_signals();
	close(pipefd[1]);
	return (pipefd[0]);
}

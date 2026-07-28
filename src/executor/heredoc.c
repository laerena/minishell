/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:13:11 by leilai            #+#    #+#             */
/*   Updated: 2026/07/28 18:20:03 by vabisco          ###   ########.fr       */
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

static int	write_heredoc_line(t_ctx *ctx, int fd,
	char *line, int do_expand)
{
	char	*expanded;

	expanded = line;
	if (do_expand)
	{
		expanded = expand_str(ctx, line);
		if (!expanded)
			return (1);
	}
	if (write(fd, expanded, ft_strlen(expanded)) == -1
		|| write(fd, "\n", 1) == -1)
	{
		if (do_expand)
			free(expanded);
		return (1);
	}
	if (do_expand)
		free(expanded);
	return (0);
}

/*
0  : continue heredoc
1  : delimiter found
-1 : error
*/
static int	process_heredoc_line(t_ctx *ctx, int fd,
		char *line, t_redircmd *redir)
{
	if (is_limiter(line, redir->file))
		return (1);
	if (write_heredoc_line(ctx, fd, line, redir->heredoc_expand))
		return (-1);
	return (0);
}

static int	fill_heredoc(t_ctx *ctx, int fd, t_redircmd *redir)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
				return (130);
			ft_eprintf(
				"warning: here-document delimited by end-of-file "
				"(wanted `%s')\n",
				redir->file);
			return (0);
		}
		ret = process_heredoc_line(ctx, fd, line, redir);
		free(line);
		if (ret == 1)
			return (0);
		if (ret == -1)
			return (1);
	}
}

int	create_heredoc(t_ctx *ctx, t_cmd *ast_node)
{
	int	pipefd[2];
	int	saved_stdin;
	int	ret;

	if (pipe(pipefd) < 0)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	g_signal = 0;
	handle_heredoc_signals();
	if (update_delimiter(&ast_node->u_cmd.redir))
		return (heredoc_abort(ctx, pipefd, saved_stdin, 1));
	ret = fill_heredoc(ctx, pipefd[1], &ast_node->u_cmd.redir);
	if (ret)
		return (heredoc_abort(ctx, pipefd, saved_stdin, ret));
	return (restore_heredoc(ctx, saved_stdin, pipefd));
}

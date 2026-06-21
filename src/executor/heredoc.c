/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:13:11 by leilai            #+#    #+#             */
/*   Updated: 2026/06/21 12:25:20 by vabisco          ###   ########.fr       */
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

int	run_heredoc(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	int	pipefd[2];
	int	exit_code;
	int	saved_fd;

	if (pipe(pipefd) < 0)
		return (ctx->last_exit_status = 1, 1);
	if (fill_heredoc(ctx, pipefd[1], ast_node))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (ctx->last_exit_status = 1, 1);
	}
	close(pipefd[1]);
	saved_fd = save_target_fd(STDIN_FILENO);
	if (apply_redirection(pipefd[0], STDIN_FILENO) == -1)
	{
		if (saved_fd >= 0)
			close (saved_fd);
		return (ctx->last_exit_status = 1, 1);
	}
	close(pipefd[0]);
	exit_code = run_ast(ctx, ast_node->u_cmd.redir.cmd, no_fork);
	if (restore_saved_fd(saved_fd, STDIN_FILENO) == 1)
		return (fail(ctx, 1, "restore_save_fd"));
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

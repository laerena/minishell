/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:05:22 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/03 15:51:39 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

static int			apply_redirs(t_ctx *ctx, t_redir *redirs);
static int			get_redir_fd(t_ctx *ctx, t_redir *redir,
						t_redir_info *r_info);
static t_redir_info	get_redir_info(t_redir_type type);

int	run_redir(t_ctx *ctx, t_cmd *node, int no_fork)
{
	int	saved[2];
	int	exit_code;

	if (save_redir_fds(saved))
		return (fail(ctx, 1, "save_redir_fds"));
	if (apply_redirs(ctx, node->u_cmd.redir.redirs))
	{
		restore_redir_fds(saved);
		ctx->last_exit_status = 1;
		return (1);
	}
	exit_code = run_ast(ctx, node->u_cmd.redir.cmd, no_fork);
	if (restore_redir_fds(saved) == 1)
		return (fail(ctx, 1, "restore_redir_fds"));
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

static int	apply_redirs(t_ctx *ctx, t_redir *redirs)
{
	t_redir_info	r_info;
	int				source_fd;

	while (redirs)
	{
		r_info = get_redir_info(redirs->type);
		source_fd = get_redir_fd(ctx, redirs, &r_info);
		if (source_fd < 0)
			return (1);
		if (redirect_fd(source_fd, r_info.fd) == -1)
		{
			ctx->last_exit_status = 1;
			return (1);
		}
		redirs = redirs->next;
	}
	return (0);
}

static int	get_redir_fd(t_ctx *ctx, t_redir *redir, t_redir_info *r_info)
{
	int	fd;

	if (redir->type == R_HEREDOC)
		return (create_heredoc(ctx, redir));
	fd = open(redir->file, r_info->flags, r_info->mode);
	if (fd == -1)
		return (fail(ctx, 1, "open"));
	return (fd);
}

static t_redir_info	get_redir_info(t_redir_type type)
{
	t_redir_info	info;

	ft_memset(&info, 0, sizeof(t_redir_info));
	if (type == R_INPUT)
	{
		info.fd = STDIN_FILENO;
		info.flags = O_RDONLY;
	}
	else if (type == R_OUTPUT)
	{
		info.fd = STDOUT_FILENO;
		info.flags = O_WRONLY | O_CREAT | O_TRUNC;
	}
	else if (type == R_APPEND)
	{
		info.fd = STDOUT_FILENO;
		info.flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else if (type == R_HEREDOC)
		info.fd = STDIN_FILENO;
	if (info.flags & O_CREAT)
		info.mode = 0644;
	return (info);
}

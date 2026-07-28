/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:05:22 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 17:55:50 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

static int			get_redir_fd(t_ctx *ctx, t_cmd *node, t_redir_info *r_info);
static t_redir_info	get_redir_info(t_redir_type type);

int	run_redir(t_ctx *ctx, t_cmd *node, int no_fork)
{
	t_redir_info		r_info;
	t_redir_save_fds	saved_fds;
	int					source_fd;
	int					exit_code;

	saved_fds.saved_stdin = -1;
	saved_fds.saved_stdout = -1;
	while (node->type == N_REDIR)
	{
		r_info = get_redir_info(node->u_cmd.redir.type);
		if (save_fds(r_info.fd, &saved_fds) == 1)
			return (restore_fds(&saved_fds), 1);
		source_fd = get_redir_fd(ctx, node, &r_info);
		if (source_fd < 0)
			return (restore_fds(&saved_fds), 1);
		if (redirect_fd(source_fd, r_info.fd) == -1)
			return (restore_fds(&saved_fds), 1);
		node = node->u_cmd.redir.cmd;
	}
	exit_code = run_ast(ctx, node, no_fork);
	if (restore_fds(&saved_fds) == -1)
		return (1);
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

static int	get_redir_fd(t_ctx *ctx, t_cmd *node, t_redir_info *r_info)
{
	int	fd;

	if (node->u_cmd.redir.type == R_HEREDOC)
		return (node->u_cmd.redir.heredoc_fd);
	fd = open(node->u_cmd.redir.file, r_info->flags, r_info->mode);
	if (fd == -1)
		return (perror("open"), ctx->last_exit_status = 1, -1);
	return (fd);
}

//helper ft for redir operator
//convert redir type into modes then store them in a binary code
//open() ft use this binary code to know which modes are used
//return redir_params (int*: mode, fd)
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

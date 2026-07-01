/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:05:22 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/21 12:00:55 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

static t_redir_info	get_redir_info(t_redir_type type);

int	run_redir(t_ctx *ctx, t_cmd *node, int no_fork)
{
	t_redir_info	r_info;
	int				file_fd;
	int				saved_fd;
	int				exit_code;

	if (node->u_cmd.redir.type == R_HEREDOC)
		return (run_heredoc(ctx, node, no_fork));
	r_info = get_redir_info(node->u_cmd.redir.type);
	file_fd = open(node->u_cmd.redir.file, r_info.flags, r_info.mode);
	if (file_fd < 0)
		return (fail(ctx, 1, "open"));
	saved_fd = save_target_fd(r_info.fd);
	if (apply_redirection(file_fd, r_info.fd) == -1)
	{
		if (saved_fd >= 0)
			close(saved_fd);
		return (ctx->last_exit_status = 1, 1);
	}
	exit_code = run_ast(ctx, node->u_cmd.redir.cmd, no_fork);
	if (restore_saved_fd(saved_fd, r_info.fd) == 1)
		return (fail(ctx, 1, "restore_save_fd"));
	ctx->last_exit_status = exit_code;
	return (exit_code);
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
	if (info.flags & O_CREAT)
		info.mode = 0644;
	return (info);
}

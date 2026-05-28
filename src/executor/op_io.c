/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:08:50 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:52:12 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_redir_info	get_redir_info(t_redir_type type);
static int			my_dup2(int oldfd, int newfd);

int	run_pipe(t_ctx *ctx, t_cmd *ast_node)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		pipefd[2];
	int		status;
	int		exit_code;

	pipe(pipefd);
	left_pid = fork();
	if (left_pid == 0)
	{
		close(pipefd[0]);
		my_dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(executor(ctx, ast_node->u_cmd.binop.left));
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		close(pipefd[1]);
		my_dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(executor(ctx, ast_node->u_cmd.binop.right));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	exit_code = convert_status_to_exitcode(status);
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

int	run_redir(t_ctx *ctx, t_cmd *ast_node)
{
	t_redir_info	r_info;
	int				fd;
	int				exit_code;

	if (ast_node->u_cmd.redir.type == R_HEREDOC)
		return (run_heredoc(ctx, ast_node));
	r_info = get_redir_info(ast_node->u_cmd.redir.type);
	fd = open(ast_node->u_cmd.redir.file, r_info.flags, r_info.mode);
	if (fd < 0)
	{
		perror("open");
		ctx->last_exit_status = 1;
		return (1);
	}
	if (my_dup2(fd, r_info.fd) < 0)
	{
		perror("dup2");
		close(fd);
		ctx->last_exit_status = 1;
		return (1);
	}
	close(fd);
	exit_code = executor(ctx, ast_node->u_cmd.redir.cmd);
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

static int	my_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror("dup2");
		close(oldfd);
		return (1);
	}
	close(oldfd);
	return (0);
}

#include "executor.h"

static t_redir_info	get_redir_info(t_redir_type type);
static int			my_dup2(int oldfd, int newfd);
static void	handle_left_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node);
static void	handle_right_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node);
static int	restore_fds(t_ctx *ctx);


int	run_pipe(t_ctx *ctx, t_cmd *ast_node)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		pipefd[2];
	int		status;
	int		exit_code;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		return (ctx->last_exit_status = 1, 1);
	}
	status = 0;
	left_pid = fork();
	if (left_pid == 0)
		handle_left_pid(ctx, pipefd, ast_node);
	right_pid = fork();
	if (right_pid == 0)
		handle_right_pid(ctx, pipefd, ast_node);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	exit_code = convert_status_to_exitcode(status);
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

static void	handle_left_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node)
{
	close(pipefd[0]);
	my_dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(executor(ctx, ast_node->u_cmd.binop.left));
}

static void	handle_right_pid(t_ctx *ctx, int pipefd[], t_cmd *ast_node)
{
	close(pipefd[1]);
	my_dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	exit(executor(ctx, ast_node->u_cmd.binop.right));
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
	if (my_dup2(fd, r_info.fd) == -1)
	{
		perror("dup2");
		close(fd);
		ctx->last_exit_status = 1;
		return (1);
	}
	close(fd);
	exit_code = executor(ctx, ast_node->u_cmd.redir.cmd);
	if (restore_fds(ctx) == 1)
			return (perror("restore_fds"), 1);
	return (exit_code);
}

//!\ If oldfd == newfd, dup2 is a no-op; do not close oldfd (that would close the target).
static int my_dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (0);
	if (dup2(oldfd, newfd) < 0)
	{
		perror("dup2");
		close(oldfd);
		return (1);
	}
	close(oldfd);
	return (0);
}

// restore fds to their original state
static int	restore_fds(t_ctx *ctx)
{
	if (dup2(ctx->saved_fds.save_stdin, STDIN_FILENO) == -1)
		return (1);
	if (dup2(ctx->saved_fds.save_stdout, STDOUT_FILENO) == -1)
		return (1);
	if (dup2(ctx->saved_fds.save_stderr, STDERR_FILENO) == -1)
		return (1);
	return (0);
}

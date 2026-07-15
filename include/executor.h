#ifndef EXECUTOR_H
# define EXECUTOR_H

//include
# include "minishell.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>

//struct
typedef struct s_redir_save_fds
{
	int	saved_stdin;
	int	saved_stdout;
}	t_redir_save_fds;

typedef struct s_redir_info
{
	int	fd;
	int	flags;
	int	mode;
}	t_redir_info;

typedef struct s_dynstrarr
{
	char	**strarr;
	size_t	size;
	size_t	capacity;
}	t_dynstrarr;

typedef int	(*t_fork_and_run_in)(t_ctx *ctx, t_cmd *ast_node, int no_fork);

//fts
int	executor(t_ctx *ctx, t_cmd *ast_node);
int	run_ast(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_node(t_ctx *ctx, t_cmd *ast_node, int no_fork);
//	op_control_flow.c
int	run_and(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_or(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_subshell(t_ctx *ctx, t_cmd *ast_node, int no_fork);
//	op_io.c
int	run_pipe(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_redir(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	create_heredoc(t_ctx *ctx, t_cmd *ast_node);
//		run_redir_helper.c
int	save_fds(int fd, t_redir_save_fds *saved_fds);
int	redirect_fd(int file_fd, int target_fd);
int	restore_fds(t_redir_save_fds *saved_fds);

//	run_execve.c
int	run_execve_wrapper(t_ctx *ctx, t_cmd *exec_node, int no_fork);
int	run_execve(t_ctx *ctx, t_execmd *cmd);
//	run_builtin.c
int	run_builtin(t_ctx *ctx, t_execmd *cmd);
//	bonus_wildcards.c
int	expand_wildcards(char ***args);
//	helper.c
int	exit_code_from_status(t_ctx *ctx, int status);
int	fork_and_run_in(t_ctx *ctx, t_cmd *ast_node, t_fork_and_run_in run_ft, int no_fork);

#endif

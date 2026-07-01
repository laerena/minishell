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
typedef struct s_redir_info
{
	int	fd;
	int	flags;
	int	mode;
} t_redir_info;

typedef struct s_dynstrarr
{
	char	**strarr;
	size_t	size;
	size_t	capacity;
}	t_dynstrarr;

//fts
int	executor(t_ctx *ctx, t_cmd *ast_node);
int	run_ast(t_ctx *ctx, t_cmd *ast_node, int no_fork);
//	op_control_flow.c
int	run_and(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_or(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_subshell(t_ctx *ctx, t_cmd *ast_node, int no_fork);
//	op_io.c
int	run_pipe(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_redir(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int	run_heredoc(t_ctx *ctx, t_cmd *ast_node, int no_fork);
//		run_redir_helper.c
int save_target_fd(int target_fd);
int apply_redirection(int file_fd, int target_fd);
int restore_saved_fd(int saved_fd, int target_fd);
//	run_execve.c
int	run_execve(t_ctx *ctx, t_execmd *cmd);
//	run_builtin.c
int	run_builtin(t_ctx *ctx, t_execmd *cmd);
//	bonus_wildcards.c
int	expand_wildcards(char ***args);
//	helper.c
int	exit_code_from_status(t_ctx *ctx, int status);
int	restore_fds(t_ctx *ctx);
int	fork_and_run(t_ctx *ctx, t_cmd *ast_node);

#endif

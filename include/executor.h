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
}	t_redir_info;

typedef struct s_dynstrarr
{
	char	**strarr;
	size_t	size;
	size_t	capacity;
}	t_dynstrarr;

//fts
int	executor(t_ctx *ctx, t_cmd *ast_node);
//	op_control_flow.c
int	run_and(t_ctx *ctx, t_cmd *ast_node);
int	run_or(t_ctx *ctx, t_cmd *ast_node);
int	run_subshell(t_ctx *ctx, t_cmd *ast_node);
//	op_io.c
int	run_pipe(t_ctx *ctx, t_cmd *ast_node);
int	run_redir(t_ctx *ctx, t_cmd *ast_node);
int	run_heredoc(t_ctx *ctx, t_cmd *ast_node);
//	run_execve.c
int	run_execve_wrapper(t_ctx *ctx, t_cmd *ast_node);
//	run_builtin.c
int	run_builtin(t_ctx *ctx, t_cmd *ast_node);
//	bonus_wildcards.c
int	expand_wildcards(char ***args);
//	helper.c
int	convert_status_to_exitcode(int status);

#endif

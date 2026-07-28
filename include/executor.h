/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:47:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:48:40 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

//include
# include "minishell.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>

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

typedef int	(*t_fork_and_run_ft)(t_ctx *ctx, t_cmd *ast_node, int no_fork);

//fts
int		executor(t_ctx *ctx, t_cmd *ast_node);
int		prepare_redirs(t_ctx *ctx, t_cmd *node);
int		run_ast(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int		run_node(t_ctx *ctx, t_cmd *ast_node, int no_fork);
void	close_heredoc_fds(t_cmd *node);
//	op_control_flow.c
int		run_and(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int		run_or(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int		run_subshell(t_ctx *ctx, t_cmd *ast_node);
//	op_io.c
int		run_pipe(t_ctx *ctx, t_cmd *ast_node, int no_fork);
int		run_redir(t_ctx *ctx, t_cmd *ast_node, int no_fork);
//		run_redir_helper.c
int		save_fds(int fd, t_redir_save_fds *saved_fds);
int		redirect_fd(int file_fd, int target_fd);
int		restore_fds(t_redir_save_fds *saved_fds);
//	heredoc.
int		create_heredoc(t_ctx *ctx, t_cmd *ast_node);
//		heredoc_cleanup.c
int		heredoc_abort(t_ctx *ctx, int pipefd[2],
			int saved_stdin, int status);
int		restore_heredoc(t_ctx *ctx, int saved_stdin, int pipefd[2]);
//	run_execve.c
int		run_execve_wrapper(t_ctx *ctx, t_cmd *exec_node, int no_fork);
//		run_execve_error.c
int		check_exec_path(t_ctx *ctx, char *path);
int		exec_not_found(t_ctx *ctx, char *cmd, char **dirs_path);
int		exec_error(t_ctx *ctx, char *exec_path, char **dirs_path);
int		run_execve(t_ctx *ctx, t_execmd *cmd);
//	run_builtin.c
int		run_builtin(t_ctx *ctx, t_execmd *cmd);
//	helper.c
int		exit_code_from_status(t_ctx *ctx, int status);
int		fork_and_run_in(t_ctx *ctx, t_cmd *ast_node,
			t_fork_and_run_ft run_ft, int no_fork);
void	run_child(t_ctx *ctx, t_cmd *node,
			t_fork_and_run_ft run_ft, int no_fork);
char	*remove_quotes(char *s);

#endif

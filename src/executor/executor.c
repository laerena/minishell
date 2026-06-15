/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:32:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/15 15:58:35 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

// static int	is_builtin_cmd(t_cmd *cmd);
static int	run_node(t_ctx *ctx, t_cmd *ast_node);
int	run_in_child(t_ctx *ctx, t_cmd *ast_node);

// check if the next node is a builtin cmd then run it directly
// or if not run_in_child the next node
// update last_exit_status
// return exit code (int: 0-255)

//run_builtin_or_child became executor, a dispatcher,
//and main entry point of the executor part of minishell
//entry point of all ast_node execution
int	executor(t_ctx *ctx, t_cmd *ast_node)
{
	int	exit_code;

	if (!ast_node)
		return (1);
	if (ast_node->type == N_EXEC
		&& ast_node->u_cmd.exec.builtin)
			exit_code = run_builtin(ctx, ast_node);
	else
		exit_code = run_in_child(ctx, ast_node);
	return (exit_code);
}

//check if the node is an exec node
//then check if this exec node contains a builtin cmd
//return TRUE (int: 1) if it contains a builtincmd otherwise FALSE (int: 0)

//moved and simplified to parser_utils.c
//to be used in cmd_new.c by ft:"(t_cmd	*new_exec_node(char **argv)"
//now it should update the struct t_execmd->is_builtin when parsing

//static int	is_builtin_cmd(t_cmd *cmd)
// {
// 	char		*cmd_name;
// 	size_t		i;
// 	size_t		builtin_len;
// 	static char	*builtincmds[] = {
// 		"cd", "echo", "export", "unset", "env", "exit", "pwd",
// 		NULL
// 	};

// 	if (cmd->type != N_EXEC)
// 		return (FALSE);
// 	cmd_name = cmd->u_cmd.exec.argv[0];
// 	i = 0;
// 	while (builtincmds[i])
// 	{
// 		builtin_len = ft_strlen(builtincmds[i]) + 1;
// 		if (ft_strncmp(builtincmds[i], cmd_name, builtin_len) == 0)
// 			return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }

static int	run_node(t_ctx *ctx, t_cmd *ast_node)
{
	if (ast_node->type == N_EXEC)
		return (run_exec(ctx, ast_node));
	else if (ast_node->type == N_PIPE)
		return (run_pipe(ctx, ast_node));
	else if (ast_node->type == N_REDIR)
		return (run_redir(ctx, ast_node));
	else if (ast_node->type == N_AND)
		return (run_and(ctx, ast_node));
	else if (ast_node->type == N_OR)
		return (run_or(ctx, ast_node));
	else if (ast_node->type == N_SUBSHELL)
		return (run_subshell(ctx, ast_node));
	else
	{
		ft_eprintf("wrong node->type: %i\n", ast_node->type);
		//fcleanup(ctx), may handle fcleanup in the main;
		ctx->last_exit_status = 127;
		return (127);
	}
}

//create a child to run the next ast_node inside and wait for it
//return the exit code (int: 0-255)
int	run_in_child(t_ctx *ctx, t_cmd *ast_node)
{
	pid_t	child_pid;
	int		status;
	int		exit_code;

	child_pid = fork();
	if (child_pid == 0)
	{
		/* DEBUG: show child pid and whether stdout is a tty */
        fprintf(stderr, "DEBUG: child pid=%d, isatty(1)=%d\n",
                (int)getpid(), (int)isatty(STDOUT_FILENO));
		signals_reset();
		exit(run_node(ctx, ast_node));
	}
	waitpid(child_pid, &status, 0);
	exit_code = convert_status_to_exitcode(status);
	ctx->last_exit_status = exit_code;
	return (exit_code);
}

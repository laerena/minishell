/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 12:32:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/27 17:51:00 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

static void	remove_empty_unquoted_args(char **argv);
static void	finalize_argv(char **argv);

void	print_ast(t_cmd *cmd);

//wrapper : entry point
//start the recursive execution of the ast
int	executor(t_ctx *ctx, t_cmd *ast_node)
{
	int	ret;

	// print_ast(ast_node);
	ret = prepare_redirs(ctx, ast_node);
	// print_ast(ast_node);
	if (ret == 0)
		ret = run_ast(ctx, ast_node, 0);
	close_heredoc_fds(ast_node);
	return (ret);
}

int	run_ast(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	if (!ast_node)
		return (1);
	/*debug*/
	// printf("node type = %i\n", ast_node->type);
	/*debug*/
	if (ast_node->type == N_EXEC)
		return (run_node(ctx, ast_node, no_fork));
	else if (ast_node->type == N_PIPE)
		return (run_pipe(ctx, ast_node, no_fork));
	else if (ast_node->type == N_REDIR)
		return (run_redir(ctx, ast_node, no_fork));
	else if (ast_node->type == N_AND)
		return (run_and(ctx, ast_node, no_fork));
	else if (ast_node->type == N_OR)
		return (run_or(ctx, ast_node, no_fork));
	else if (ast_node->type == N_SUBSHELL)
		return (run_subshell(ctx, ast_node, no_fork));
	else
	{
		ft_eprintf("wrong node->type: %i\n", ast_node->type);
		//fcleanup(ctx), may handle fcleanup in the main;
		ctx->last_exit_status = 127;
		return (127);
	}
}

int	run_node(t_ctx *ctx, t_cmd *ast_node, int no_fork)
{
	t_execmd	*cmd;

	cmd = &ast_node->u_cmd.exec;
	//debug
	// printf("ARGV BEFORE EXPAND:\n");
	// for (int i = 0; cmd->argv[i]; i++)
	// 	printf("[%d] = %s\n", i, cmd->argv[i]);
	//debug
	if (expand_argv(ctx, cmd->argv) == 1)
		return (1);
	//debug
	// printf("AFTER EXPAND:\n");
	// for (int i = 0; cmd->argv[i]; i++)
	// 	printf("[%d] = %s\n", i, cmd->argv[i]);
	//debug
	remove_empty_unquoted_args(cmd->argv);
	if (cmd->argv && cmd->argv[0])
	{
		if (expand_wildcards(&cmd->argv) == 1)
			return (1);
		//debug
		// printf("AFTER WILDCARD:\n");
		// for (int i = 0; cmd->argv[i]; i++)
		// 	printf("[%d] = %s\n", i, cmd->argv[i]);
		//debug
	}
	finalize_argv(cmd->argv);
	if (cmd->builtin != BUILTIN_NONE)
		return (run_builtin(ctx, cmd, no_fork));
	else if(no_fork == 1)
		return(run_execve(ctx, cmd));
	return (fork_and_run_in(ctx, ast_node, run_execve_wrapper, no_fork));
}

static void	remove_empty_unquoted_args(char **argv)
{
	size_t	i;
	size_t	j;

	if (!argv)
		return ;
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			argv[j++] = argv[i];
		else
			free(argv[i]);
		i++;
	}
	argv[j] = NULL;
}


static void	finalize_argv(char **argv)
{
	size_t	i;
	char	*tmp;
	
	i = 0;
	while (argv[i])
	{
		tmp = remove_quotes(argv[i]);
		if (!tmp)
			return ;
		free(argv[i]);
		argv[i] = tmp;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:30:45 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:09:24 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

//main ft to handle builtin cmds
//expand wildcards then exec the correct builtin cmds
//propagate the error return;
int	run_builtin(t_ctx *ctx, t_cmd *ast_node)
{
	t_execmd	*exec;

	exec = &ast_node->u_cmd.exec;
	if (expand_wildcards(&exec->argv) == 1)
		return (ctx->last_exit_status = 1, 1);
	if (exec->builtin == BUILTIN_ECHO)
		return (builtin_echo(ctx, exec->argv + 1));
	else if (exec->builtin == BUILTIN_CD)
		return (builtin_cd(ctx, exec->argv + 1));
	else if (exec->builtin == BUILTIN_PWD)
		return (builtin_pwd(ctx));
	else if (exec->builtin == BUILTIN_EXPORT)
		return (builtin_export(ctx, exec->argv + 1));
	else if (exec->builtin == BUILTIN_UNSET)
		return (builtin_unset(ctx, exec->argv + 1));
	else if (exec->builtin == BUILTIN_ENV)
		return (builtin_env(ctx->envp));
	else if (exec->builtin == BUILTIN_EXIT)
		builtin_exit(ctx);
	else
		return (1);
	return(0);
}

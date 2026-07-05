/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:09:26 by leilai            #+#    #+#             */
/*   Updated: 2026/07/05 15:47:36 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
/*
** (recursively) Walk AST:
**
** if EXEC: expand argv
** if REDIR: expand child + file
** if PIPE/AND/OR: expand left + right
** if SUBSHELL: expand child
*/

int	expand_argv(t_ctx *ctx, char **argv)
{
	int		i;
	char	*new;

	i = 0;
	while (argv && argv[i])
	{
		new = expand_str(ctx, argv[i]);
		if (!new)
			return (1);
		free(argv[i]);
		argv[i] = new;
		i++;
	}
	return (0);
}

static int	expand_redir(t_ctx *ctx, t_cmd *cmd)
{
	char	*new;

	if (expand_ast(ctx, cmd->u_cmd.redir.cmd))
		return (1);
	if (cmd->u_cmd.redir.type == R_HEREDOC)
	{
		new = strip_heredoc_quotes(cmd->u_cmd.redir.file,
				&cmd->u_cmd.redir.heredoc_expand);
		if (!new)
			return (1);
		free(cmd->u_cmd.redir.file);
		cmd->u_cmd.redir.file = new;
		return (0);
	}
	new = expand_str(ctx, cmd->u_cmd.redir.file);
	if (!new)
		return (1);
	free(cmd->u_cmd.redir.file);
	cmd->u_cmd.redir.file = new;
	return (0);
}

static int	expand_binop(t_ctx *ctx, t_cmd *cmd)
{
	if (expand_ast(ctx, cmd->u_cmd.binop.left))
		return (1);
	if (expand_ast(ctx, cmd->u_cmd.binop.right))
		return (1);
	return (0);
}

int	expand_ast(t_ctx *ctx, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->type == N_EXEC)
		return (expand_argv(ctx, cmd->u_cmd.exec.argv));
	if (cmd->type == N_REDIR)
		return (expand_redir(ctx, cmd));
	if (cmd->type == N_PIPE || cmd->type == N_AND || cmd->type == N_OR)
		return (expand_binop(ctx, cmd));
	if (cmd->type == N_SUBSHELL)
		return (expand_ast(ctx, cmd->u_cmd.subshell.child));
	return (0);
}

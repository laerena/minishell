/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:51:50 by leilai            #+#    #+#             */
/*   Updated: 2026/05/28 13:17:45 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*cmd_alloc(t_node_type type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->type = type;
	return (cmd);
}

t_cmd	*new_exec_node(char **argv)
{
	t_cmd	*cmd;

	if (!argv)
		return (NULL);
	cmd = cmd_alloc(N_EXEC);
	if (!cmd)
		return (NULL);
	cmd->u_cmd.exec.argv = argv;
	cmd->u_cmd.exec.builtin = BUILTIN_NONE;
	if (argv[0])
		cmd->u_cmd.exec.builtin = is_builtin_cmd(argv[0]);
	return (cmd);
}

t_cmd	*new_binop_node(t_node_type type, t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	cmd = cmd_alloc(type);
	if (!cmd)
	{
		cmd_clear(&left);
		cmd_clear(&right);
		return (NULL);
	}
	cmd->u_cmd.binop.left = left;
	cmd->u_cmd.binop.right = right;
	return (cmd);
}

t_cmd	*new_redir_node(t_cmd *child, char *file, t_redir_type type)
{
	t_cmd	*cmd;

	cmd = cmd_alloc(N_REDIR);
	if (!cmd)
	{
		cmd_clear(&child);
		free(file);
		return (NULL);
	}
	cmd->u_cmd.redir.cmd = child;
	cmd->u_cmd.redir.file = file;
	cmd->u_cmd.redir.type = type;
	cmd->u_cmd.redir.heredoc_expand = 1;
	return (cmd);
}

/* 
** parser only creates this structure
** executor decides to fork or subshell behavior
*/
t_cmd	*new_subshell_node(t_cmd *child)
{
	t_cmd	*cmd;

	cmd = cmd_alloc(N_SUBSHELL);
	if (!cmd)
	{
		cmd_clear(&child);
		return (NULL);
	}
	cmd->u_cmd.subshell.child = child;
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:51:50 by leilai            #+#    #+#             */
/*   Updated: 2026/05/11 19:30:25 by leilai           ###   ########.fr       */
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

t_cmd	*new_exec_node(char **av)
{
	t_cmd	*cmd;

	cmd = cmd_alloc(N_EXEC);
	if (!cmd)
		return (NULL);
	cmd->u_cmd.exec.av = av;
	return (cmd);
}

t_cmd	*new_binop_node(t_node_type type, t_cmd *left, t_cmd *right)
{
	t_cmd	*cmd;

	cmd = cmd_alloc(type);
	if (!cmd)
		return (NULL);
	cmd->u_cmd.binop.left = left;
	cmd->u_cmd.binop.right = right;
	return (cmd);
}

t_cmd	*new_redir_node(t_cmd *child, char *file, t_redir_mode mode)
{
	t_cmd	*cmd;

	cmd = cmd_alloc(N_REDIR);
	if (!cmd)
		return (NULL);
	cmd->u_cmd.redir.cmd = child;
	cmd->u_cmd.redir.file = file;
	cmd->u_cmd.redir.mode = mode;
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
		return (NULL);
	cmd->u_cmd.subshell.child = child;
	return (cmd);
}

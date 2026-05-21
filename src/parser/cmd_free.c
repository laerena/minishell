/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:59:38 by leilai            #+#    #+#             */
/*   Updated: 2026/05/21 16:28:34 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	clear_redir(t_cmd *cmd)
{
	cmd_clear(&cmd->u_cmd.redir.cmd);
	free(cmd->u_cmd.redir.file);
}

static void	clear_binop(t_cmd *cmd)
{
	cmd_clear(&cmd->u_cmd.binop.left);
	cmd_clear(&cmd->u_cmd.binop.right);
}

/*
** frees the whole AST recursively
**
** checks the node type and
** frees only the union field valid for that type
** - N_EXEC					uses u_cmd.exec
** - N_PIPE/N_AND/N_OR		uses u_cmd.binop
** - N_REDIR 				uses u_cmd.redir
** - N_SUBSHELL				uses u_cmd.subshell
** 
*/
void	cmd_clear(t_cmd **cmd)
{
	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->type == N_EXEC)
		free_argv((*cmd)->u_cmd.exec.argv);
	else if ((*cmd)->type == N_PIPE || (*cmd)->type == N_AND
		|| (*cmd)->type == N_OR)
		clear_binop(*cmd);
	else if ((*cmd)->type == N_REDIR)
		clear_redir(*cmd);
	else if ((*cmd)->type == N_SUBSHELL)
		cmd_clear(&(*cmd)->u_cmd.subshell.child);
	free(*cmd);
	*cmd = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:37:51 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 19:18:03 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

/*
Parse the ast to handle heredoc inputs and store fd
*/
// int	process_heredocs(t_ctx *ctx, t_cmd *node)
// {
// 	if (!node)
// 		return (0);
// 	if (node->type == N_REDIR)
// 	{
// 		if (node->u_cmd.redir.type == R_HEREDOC)
// 		{
// 			node->u_cmd.redir.heredoc_fd = create_heredoc(ctx, node);
// 			if (node->u_cmd.redir.heredoc_fd < 0)
// 				return (1);
// 		}
// 		return (process_heredocs(ctx, node->u_cmd.redir.cmd));
// 	}
// 	if (node->type == N_PIPE
// 		|| node->type == N_AND
// 		|| node->type == N_OR)
// 	{
// 		if (process_heredocs(ctx, node->u_cmd.binop.left))
// 			return (1);
// 		return (process_heredocs(ctx, node->u_cmd.binop.right));
// 	}
// 	if (node->type == N_SUBSHELL)
// 		return (process_heredocs(ctx, node->u_cmd.subshell.child));
// 	return (0);
// }

/*
Parse the ast to clear heredoc s fds
*/
void	close_heredoc_fds(t_cmd *node)
{
	if (!node)
		return ;
	if (node->type == N_REDIR)
	{
		if (node->u_cmd.redir.type == R_HEREDOC
			&& node->u_cmd.redir.heredoc_fd >= 0)
		{
			close(node->u_cmd.redir.heredoc_fd);
			node->u_cmd.redir.heredoc_fd = -1;
		}
		close_heredoc_fds(node->u_cmd.redir.cmd);
	}
	else if (node->type == N_PIPE
		|| node->type == N_AND
		|| node->type == N_OR)
	{
		close_heredoc_fds(node->u_cmd.binop.left);
		close_heredoc_fds(node->u_cmd.binop.right);
	}
	else if (node->type == N_SUBSHELL)
		close_heredoc_fds(node->u_cmd.subshell.child);
}

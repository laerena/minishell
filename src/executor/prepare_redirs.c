/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 19:16:29 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 19:25:04 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

static int	prepare_redir(t_ctx *ctx, t_cmd *node);
static int	prepare_redir_file(t_ctx *ctx, char **file);

int	prepare_redirs(t_ctx *ctx, t_cmd *node)
{
	if (!node)
		return (0);
	if (node->type == N_REDIR)
	{
		if (prepare_redir(ctx, node))
			return (1);
		return (prepare_redirs(ctx, node->u_cmd.redir.cmd));
	}
	if (node->type == N_PIPE || node->type == N_AND
		|| node->type == N_OR)
	{
		if (prepare_redirs(ctx, node->u_cmd.binop.left))
			return (1);
		return (prepare_redirs(ctx, node->u_cmd.binop.right));
	}
	if (node->type == N_SUBSHELL)
		return (prepare_redirs(ctx, node->u_cmd.subshell.child));
	return (0);
}

static int	prepare_redir(t_ctx *ctx, t_cmd *node)
{
	t_redircmd	*redir;

	redir = &node->u_cmd.redir;
	if (redir->type == R_HEREDOC)
	{
		redir->heredoc_fd = create_heredoc(ctx, node);
		if (redir->heredoc_fd < 0)
			return (1);
		return (0);
	}
	return (prepare_redir_file(ctx, &redir->file));
}

static int	prepare_redir_file(t_ctx *ctx, char **file)
{
	char	*tmp;

	tmp = expand_str(ctx, *file);
	if (!tmp)
		return (1);
	free(*file);
	*file = tmp;
	tmp = remove_quotes(*file);
	if (!tmp)
		return (1);
	free(*file);
	*file = tmp;
	return (0);
}

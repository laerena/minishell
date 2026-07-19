/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 14:22:32 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/19 14:40:43 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"

void	malloc_error_exit(t_ctx *ctx)
{
	ft_eprintf("minishell: malloc error\n");
	cmd_clear(&ctx->ast_head);
	ft_strarr_free(ctx->envp);
	rl_clear_history();
	exit(1);
}

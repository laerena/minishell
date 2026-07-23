/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:57:05 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/23 19:06:39 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_strarr_putendl_fd(char **strarr, int fd);

int	builtin_env(t_ctx *ctx, t_execmd *cmd, char **envp)
{
	if (cmd->argv[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ctx->last_exit_status = 127;
		return (127);
	}
	ctx->last_exit_status = ft_strarr_putendl_fd(envp, 1);
	return (ctx->last_exit_status);
}

static int	ft_strarr_putendl_fd(char **strarr, int fd)
{
	while (*strarr)
	{
		if (ft_strchr(*strarr, '='))
			if (ft_putendl_fd(*strarr, fd) == -1)
				return (1);
		strarr++;
	}
	return (0);
}

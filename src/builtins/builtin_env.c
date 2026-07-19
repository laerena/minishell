/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:57:05 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/19 13:13:57 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_strarr_putendl_fd(char **strarr, int fd);

int	builtin_env(t_ctx *ctx, char **envp)
{
	int	exit_code;

	exit_code = ft_strarr_putendl_fd(envp, 1);
	ctx->last_exit_status = exit_code;
	return(exit_code);
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

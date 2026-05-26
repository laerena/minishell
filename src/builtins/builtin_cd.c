/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:03:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:19:02 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"

int	builtin_cd(t_ctx *ctx, char **args)
{
	char *path;

	if (args[1])
	{
		ft_eprintf("cd: too many arguments\n");
		return (ctx->last_exit_status = 1, 1);
	}
	path = args[0];
	// if (!path)
	// 	path = expand_str(ctx, "HOME");
	// ft_printf("PATH=%s\n", path);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (ctx->last_exit_status = 1, 1);
	}
	return (ctx->last_exit_status = 0, 0);
}

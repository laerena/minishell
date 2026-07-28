/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:03:04 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 17:40:25 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"

int	builtin_cd(t_ctx *ctx, char **args)
{
	char	*path;

	if (args[0] == NULL)
		path = expand_str(ctx, "$HOME");
	else if (args[1])
	{
		ft_eprintf("cd: too many arguments\n");
		return (ctx->last_exit_status = 1, 1);
	}
	else
		path = args[0];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (ctx->last_exit_status = 1, 1);
	}
	return (ctx->last_exit_status = 0, 0);
}

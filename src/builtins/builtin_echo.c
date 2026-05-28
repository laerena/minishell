/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:59:01 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/28 16:20:58 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//display a line of text on stdout
//option: -n: do not output the trailing newline
//as simple as possible for what we need
int	builtin_echo(t_ctx *ctx, char **args)
{
	int		has_newline;

	has_newline = 1;
	while (*args)
	{
		if (ft_strncmp("-n", *args, 3) == 0)
			has_newline = 0;
		else
			break ;
		args++;
	}
	while (*args)
	{
		if (write(1, *args, ft_strlen(*args)) == -1)
			return (ctx->last_exit_status = 1, 1);
		// if (write(1, "", 1) == -1)
		// 	return (ctx->last_exit_status = 1, 1);
		args++;
	}
	if (has_newline == 1)
			if (write (1, "\n", 1) == -1)
				return (ctx->last_exit_status = 1, 1);
	return (ctx->last_exit_status = 0, 0);
}

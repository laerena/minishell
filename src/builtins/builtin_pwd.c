/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:57:26 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:10:43 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(t_ctx *ctx)
{
	char	buf[256];

	if (getcwd(buf, 256) == NULL)
	{
		perror("pwd");
		return (ctx->last_exit_status = 1, 1);
	}
	if (write(1, buf, ft_strlen(buf)) == -1)
		return (ctx->last_exit_status = 1, 1);
	if (write(1, "\n", 1) == -1)
		return (ctx->last_exit_status = 1, 1);
	return (0);
}

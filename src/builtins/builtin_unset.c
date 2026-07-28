/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:04:00 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 17:37:09 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	remove_envp_var(t_ctx *ctx, size_t i);

/*
* Remove each requested variable from the shell environment.
* The environment array is shifted after deletion to keep it contiguous.
*/
int	builtin_unset(t_ctx *ctx, char **args)
{
	size_t	name_len;
	size_t	i;

	while (*args)
	{
		i = 0;
		while (ctx->envp[i])
		{
			name_len = ft_strclen(ctx->envp[i], '=');
			if (ft_strncmp(ctx->envp[i], *args, name_len) == 0
				&& (ctx->envp[i])[name_len] == '=' && (*args)[name_len] == '\0')
				break ;
			i++;
		}
		if (ctx->envp[i])
			if (remove_envp_var(ctx, i))
				return (ctx->last_exit_status = 1, 1);
		args++;
	}
	return (ctx->last_exit_status = 0, 0);
}

static int	remove_envp_var(t_ctx *ctx, size_t i)
{
	size_t	envp_size;

	envp_size = ft_arrlen((void **)ctx->envp);
	free(ctx->envp[i]);
	ft_memmove(ctx->envp + i,
		ctx->envp + i + 1,
		(envp_size - i) * sizeof(char *));
	ctx->envp = ft_realloc(ctx->envp,
			(envp_size + 1) * sizeof(char *),
			envp_size * sizeof(char *));
	if (!ctx->envp)
		return (1);
	return (0);
}

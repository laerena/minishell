/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:04:00 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:10:43 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_unset(t_ctx *ctx, char **args)
{
	size_t	envp_size;
	size_t	name_len;
	size_t	i;
	
	while (*args)
	{
		i = 0;
		while (ctx->envp[i])
		{
			name_len = ft_strlen(*args);
			if (ft_strncmp(ctx->envp[i], *args, name_len) == 0
				&& (ctx->envp[i])[name_len] == '=' && (*args)[name_len] == '\0')
				break;
			i++;
		}
		/*debug*/ ft_printf("pos=%s[%zu]\n", ctx->envp[i], i);
		//breakpoint
		if (ctx->envp[i])
		{
			envp_size = ft_arrlen((void **)ctx->envp);
			/*debug*/ ft_printf("envp+size=%zu\n", envp_size);
			free(ctx->envp[i]);
			ft_memmove(ctx->envp + i, ctx->envp + i + 1, (envp_size - i) * sizeof(char *));
			ctx->envp = ft_realloc(ctx->envp, (envp_size + 1) * sizeof(char *), (envp_size - 1 + 1) * sizeof(char *));
			if (!ctx->envp)
				return (ctx->last_exit_status = 1, 1);
		}
		args++;
	}
	return (ctx->last_exit_status = 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:56:43 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/15 15:25:53 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static int	process_export(t_ctx *ctx, char **args);
static int	add_var(t_ctx *ctx, char **args);

int	builtin_export(t_ctx *ctx, char **args)
{
	if (!*args)
		return (export_p(ctx->envp));
	if (process_export(ctx, args) == 1)
		return (ctx->last_exit_status = 1, 1);
	return (ctx->last_exit_status = 0, 0);
}

static int	process_export(t_ctx *ctx, char **args)
{
	char	**var;
	char	*tmp;

	while (*args)
	{
		var = find_var_in_envp(ctx->envp, *args);
		if (*var == NULL) //if var not found
		{
			if(add_var(ctx, args) == 1)
				return (ctx->last_exit_status = 1, 1);
		}
		else if (ft_strchr(*args, '=') && ft_strcmp(*var, *args) != 0) //if var found but value not equal (have '=')
		{
			tmp = ft_strdup(*args);
			if (!tmp)
				return (ctx->last_exit_status = 1, 1);
			free(*var);
			*var = tmp;
		}
		args++;
	}
	return (0);
}

static int	add_var(t_ctx *ctx, char **args)
{
	size_t	envp_size;

	envp_size = ft_arrlen((void **)ctx->envp);
	ctx->envp = ft_realloc(ctx->envp, envp_size * sizeof(char *), (envp_size + 2) * sizeof(char *));
	if (!ctx->envp)
		return (ctx->last_exit_status = 1, 1);
	ctx->envp[envp_size] = ft_strdup(*args);
	ctx->envp[envp_size + 1] = NULL;
	return (ctx->last_exit_status = 0, 0);
}

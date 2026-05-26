/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:56:43 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:26:40 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_export(t_ctx *ctx, char **args)
{
	char	**envp;
	char	*tmp;
	size_t	envp_size;

	while (*args)
	{
		if (!ft_strchr(*args, '=')) // if var has no value (=), I do not export shell var
		{
			perror("export");
			ft_printf("export shell variable is not handled\n");
			args++;
			continue ;
		}
		envp = ctx->envp;
		while (*envp)
		{
			if (ft_strncmp(*args, *envp, ft_strclen(*args, '=')) == 0)
				break;
			envp++;
		}
		if (*args && *envp && ft_strcmp(*args, *envp) == 0) //if var found and value equal
			return (ctx->last_exit_status = 0, 0);
		if (*envp != NULL)	//if var found but value not equal
		{
			tmp = *envp;
			*envp = ft_strdup(*args);
			free(tmp);
		}
		else //if var not found
		{
			envp_size = ft_arrlen((void **)ctx->envp);
			ctx->envp = ft_realloc(ctx->envp, envp_size * sizeof(char *), (envp_size + 2) * sizeof(char *));
			if (!ctx->envp)
				return (ctx->last_exit_status = 1, 1);
			ctx->envp[envp_size] = ft_strdup(*args);
			ctx->envp[envp_size + 1] = NULL;
		}
		args++;
	}
	return (ctx->last_exit_status = 0, 0);
}

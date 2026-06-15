/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:27:46 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/15 15:42:02 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

//dup **envp locally to allow modifications on it
//(need a local cpy of **envp, can t modify the original)
int	init_envp(t_ctx *ctx, char **envp)
{
	size_t	i;

	i = 0;
	if (!envp || !envp[0])
	{
		ctx->envp = ft_calloc(1, sizeof(char *));
		if (!ctx->envp)
			return (1);
		return (0);
	}
	while (envp[i])
		i++;
	ctx->envp = ft_calloc((i + 1), sizeof(char *));
	if (!ctx->envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		ctx->envp[i] = ft_strdup(envp[i]);
		if (!ctx->envp[i])
			return (ft_strarr_free(ctx->envp), 1);
		i++;
	}
	return (0);
}

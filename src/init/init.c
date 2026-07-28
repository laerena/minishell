/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vabisco <vabisco@student.42lausanne.ch>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/06/18 12:46:59 by vabisco		   #+#	#+#			 */
/*   Updated: 2026/06/18 16:57:06 by vabisco		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "init.h"

static int	init_envp(t_ctx *ctx, char **envp);

int	init(t_ctx *ctx, char **envp)
{
	ctx->is_main_shell = 1;
	if (init_envp(ctx, envp) == 1)
		return (perror("init_envp"), 1);
	if (update_shlvl(ctx) == 1)
		return (perror("update_shlvl"), 1);
	return (0);
}

//dup **envp locally to allow modifications on it
//(need a local cpy of **envp, can t modify the original)
static int	init_envp(t_ctx *ctx, char **envp)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:56:43 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/09 19:04:52 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_strarr_sort(char **args);
static int export_p(char **envp);
static int	export_p_print(char **cpy, size_t n);

int	builtin_export(t_ctx *ctx, char **args)
{
	char	**envp;
	char	*tmp;
	size_t	envp_size;

	if (!*args)
		export_p(ctx->envp);
	while (*args)
	{
		// if (!ft_strchr(*args, '=')) // if var has no value (=), I do not export shell var
		// {
		// 	perror("export");
		// 	ft_printf("export shell variable is not handled\n");
		// 	args++;
		// 	continue ;
		// }
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

static void	ft_strarr_sort(char **args)
{
	size_t	i;
	char	*tmp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (args[i] && args[i + 1])
		{
			if (ft_strncmp(args[i], args[i + 1], 1) > 0)
			{
				tmp = args[i];
				args[i] = args[i + 1];
				args[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static int	export_p(char **envp)
{
	size_t	n;
	char	**cpy;
	size_t	i;

	n = ft_arrlen((void **)envp);
	cpy = malloc((n + 1) * sizeof(char *));
	if (!cpy)
		return (1);
	i = 0;
	while (i < n)
	{
		cpy[i] = envp[i];
		i++;
	}
	cpy[i] = NULL;
	ft_strarr_sort(cpy);
	export_p_print(cpy, n);
	free(cpy);
	return (0);
}

static int	export_p_print(char **cpy, size_t n)
{
	size_t	i;
	char	*sep;
	char	*name;
	char	*value;
	
	i = 0;
	while (i < n)
	{
		sep = ft_strchr(cpy[i], '=');
		if (sep == NULL)
			return (ft_printf("declare -x %s\n", cpy[i]), 0);
		name = ft_substr(cpy[i], 0, (size_t)(sep - 0));
		value = sep + 1;
		ft_printf("declare -x %s=\"%s\"\n", name, value);
		i++;
	}
	return (0);
}

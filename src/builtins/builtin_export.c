/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:56:43 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 18:19:06 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static int	process_arg(t_ctx *ctx, char *arg, int *status);
static int	is_valid_identifier(char *arg);
static int	add_var(t_ctx *ctx, char *arg);
static int	update_var(char **var, char *arg);

/*
* Export variables to the environment.
* If called without arguments, prints all exported variables.
*/
int	builtin_export(t_ctx *ctx, char **args)
{
	int	status;

	if (!*args)
		return (export_p(ctx->envp));
	status = 0;
	while (*args)
	{
		if (process_arg(ctx, *args, &status))
			return (ctx->last_exit_status = 1, 1);
		args++;
	}
	ctx->last_exit_status = status;
	return (status);
}

/*
* Validate an export argument and either add or update the variable.
* Invalid identifiers are reported but do not stop processing.
*/
static int	process_arg(t_ctx *ctx, char *arg, int *status)
{
	char	**var;

	if (!is_valid_identifier(arg))
	{
		ft_dprintf(2,
			"minishell: export: `%s': not a valid identifier\n",
			arg);
		*status = 1;
		return (0);
	}
	var = find_var_in_envp(ctx->envp, arg);
	if (!var)
		return (add_var(ctx, arg));
	return (update_var(var, arg));
}

/*
* Check whether a string is a valid shell identifier.
* A valid identifier starts with a letter or '_', followed by
* letters, digits or '_', until an optional '='.
*/
static int	is_valid_identifier(char *arg)
{
	size_t	i;

	if (!arg || !*arg)
		return (0);
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
* Append a new variable to the environment array.
*/
static int	add_var(t_ctx *ctx, char *arg)
{
	size_t	envp_size;
	char	**tmp;

	envp_size = ft_arrlen((void **)ctx->envp);
	tmp = ft_realloc(ctx->envp,
			envp_size * sizeof(char *),
			(envp_size + 2) * sizeof(char *));
	if (!tmp)
		return (1);
	ctx->envp = tmp;
	ctx->envp[envp_size] = ft_strdup(arg);
	if (!ctx->envp[envp_size])
		return (1);
	ctx->envp[envp_size + 1] = NULL;
	return (0);
}

/*
* Update an existing environment variable if a new value is provided.
* Does nothing when no assignment is present or the value is unchanged.
*/
static int	update_var(char **var, char *arg)
{
	char	*tmp;

	if (!ft_strchr(arg, '=') || ft_strcmp(*var, arg) == 0)
		return (0);
	tmp = ft_strdup(arg);
	if (!tmp)
		return (1);
	free(*var);
	*var = tmp;
	return (0);
}

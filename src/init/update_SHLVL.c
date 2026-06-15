/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   update_SHLVL.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: vabisco <vabisco@student.42lausanne.ch>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/06/15 15:28:06 by vabisco		   #+#	#+#			 */
/*   Updated: 2026/06/15 15:28:28 by vabisco		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "init.h"
#include "utils.h"
#include "builtins.h"

static long long	parse_shlvl_slot(char **slot);
static long long	normalize_shlvl(long long value);
static char			*build_shlvl_var(long long value);

/* public entry: updates SHLVL in ctx->envp using builtin_export */
int	update_shlvl(t_ctx *ctx)
{
	char		**slot;
	long long	value;
	char		*var;

	if (!ctx)
		return (1);
	slot = find_var_in_envp(ctx->envp, "SHLVL");
	if (!slot)
		return (1);
	value = parse_shlvl_slot(slot);
	value = normalize_shlvl(value);
	var = build_shlvl_var(value);
	if (!var)
		return (1);
	if (builtin_export(ctx, (char *[]){var, NULL}) == 1)
		return (free(var), 1);
	free(var);
	return (0);
}

/* return numeric value of SHLVL slot, or 0 if missing/non-numeric */
static long long	parse_shlvl_slot(char **slot)
{
	char	*eq;

	if (!slot || *slot == NULL)
		return (0);
	eq = ft_strchr(*slot, '=');
	if (!eq || !*(eq + 1))
		return (0);
	return (ft_atoll(eq + 1));
}

/* increment and normalize; print warning and reset to 1 if too high */
static long long	normalize_shlvl(long long value)
{
	value += 1;
	if (value >= 1000)
	{
		ft_eprintf("minishell: warning: shell level (%lli) too high,"
			"resetting to 1\n", value);
		return (1);
	}
	return (value);
}

/* build "SHLVL=%lli", returns malloc'd string or NULL */
static char	*build_shlvl_var(long long value)
{
	char	*out;

	if (ft_asprintf(&out, "SHLVL=%lli", value) == -1)
		return (NULL);
	return (out);
}

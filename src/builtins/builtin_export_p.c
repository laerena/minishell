/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 16:08:39 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/18 11:00:57 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	export_p_print(char **cpy, size_t n);
static void	ft_strarr_sort(char **args);

/*
Flag "-p", export shall write to the standard output
the names and values of all exported variables, in the following
format:

	"export %s=%s\n", <name>, <value>

if name is set, and:

	"export %s\n", <name>
*/
int	export_p(char **envp)
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
	
	if (!cpy || n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		sep = ft_strchr(cpy[i], '=');
		if (sep == NULL)
		{
			ft_printf("declare -x %s\n", cpy[i]);
			i++;
			continue ;
		}
		name = ft_substr(cpy[i], 0, (size_t)(sep - cpy[i]));
		value = sep + 1;
		ft_printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
		i++;
	}
	return (0);
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
			if (ft_strcmp(args[i], args[i + 1]) > 0)
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

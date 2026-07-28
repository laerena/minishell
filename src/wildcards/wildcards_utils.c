/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:39:00 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:43:28 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

/*
** Processes a single directory entry during wildcard expansion.
** Hidden files are ignored unless the pattern starts with '.'.
** Matching filenames are appended to the destination array.
** Returns 0 on success and 1 on allocation failure.
*/
int	handle_entry(t_dynstrarr *w_args, const char *arg,
			struct dirent *entry)
{
	if (arg[0] != '.' && entry->d_name[0] == '.')
		return (0);
	if (ft_fnmatch_minishell(arg, entry->d_name) == 0)
	{
		if (ft_strarr_apnd(w_args, entry->d_name))
			return (1);
	}
	return (0);
}

/*
** Minimal fnmatch implementation supporting only '*'.
** Returns 0 when the filename matches the pattern,
** and 1 otherwise.
*/
int	ft_fnmatch_minishell(const char *pattern, const char *arg)
{
	if (!*pattern && !*arg)
		return (0);
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (ft_fnmatch_minishell(pattern + 1, arg) == 0)
			return (0);
		if (*arg && ft_fnmatch_minishell(pattern, arg + 1) == 0)
			return (0);
		return (1);
	}
	if (*pattern == *arg)
		return (ft_fnmatch_minishell(pattern + 1, arg + 1));
	return (1);
}

/*
** Appends a copy of a string to a dynamic string array.
** The array is automatically resized when needed.
** Returns 0 on success and 1 on allocation failure.
*/
int	ft_strarr_apnd(t_dynstrarr *w_args, const char *arg)
{
	char	**old_arr;

	if (!arg)
		return (0);
	if (w_args->size + 1 >= w_args->capacity)
	{
		old_arr = w_args->strarr;
		w_args->capacity = w_args->capacity * 2 + 2;
		w_args->strarr = ft_calloc(w_args->capacity, sizeof(char *));
		if (!w_args->strarr)
			return (1);
		ft_memcpy(w_args->strarr, old_arr, w_args->size * sizeof(char *));
		free(old_arr);
	}
	w_args->strarr[w_args->size] = ft_strdup(arg);
	if (!w_args->strarr[w_args->size])
		return (1);
	w_args->size++;
	return (0);
}

/*
** Sorts a range of a NULL-terminated string array in lexicographical order.
** Only elements starting at the given index are reordered.
** Used to reproduce Bash's behavior, where wildcard matches are
** returned in alphabetical order.
*/
void	ft_strarr_sort_range(char **args, size_t start)
{
	size_t	i;
	char	*tmp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = start;
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

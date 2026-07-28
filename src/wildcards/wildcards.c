/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:52:15 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:44:08 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	expand_arg(t_dynstrarr *w_args, char *arg);
static int	expand_single_wildcard(t_dynstrarr *w_args,
				const char *arg, size_t start);

/*
** Expands wildcard patterns in the argv array.
** The command name (argv[0]) is kept unchanged.
** Every argument containing '*' is expanded into matching filenames.
** Arguments without wildcards are copied as-is.
** If no match is found, the original pattern is preserved.
*/
int	expand_wildcards(char ***args)
{
	size_t		i;
	t_dynstrarr	w_args;

	if (!args || !*args || !(*args)[0])
		return (0);
	ft_memset(&w_args, 0, sizeof(w_args));
	if (ft_strarr_apnd(&w_args, (*args)[0]) == 1)
		return (1);
	i = 1;
	while ((*args)[i])
	{
		if (expand_arg(&w_args, (*args)[i]))
			return (1);
		i++;
	}
	if (!w_args.strarr)
		return (1);
	ft_strarr_free(*args);
	(*args) = w_args.strarr;
	return (0);
}

/*
** Expands a single command argument.
** Arguments without wildcards are copied directly.
** Wildcard patterns are expanded and the resulting matches
** are sorted in lexicographical order.
*/
static int	expand_arg(t_dynstrarr *w_args, char *arg)
{
	size_t	start;

	if (!ft_strchr(arg, '*'))
		return (ft_strarr_apnd(w_args, arg));
	start = w_args->size;
	if (expand_single_wildcard(w_args, arg, start))
		return (1);
	ft_strarr_sort_range(w_args->strarr, start);
	return (0);
}

/*
** Expands a single wildcard pattern.
** Scans the current directory and appends every matching filename.
** Hidden files are ignored unless the pattern starts with '.'.
** If no filename matches, the original pattern is appended unchanged.
*/
static int	expand_single_wildcard(t_dynstrarr *w_args,
			const char *arg, size_t start)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		if (ft_strarr_apnd(w_args, arg) == 1)
			return (1);
		return (0);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (handle_entry(w_args, arg, entry))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (w_args->size == start)
		return (ft_strarr_apnd(w_args, arg));
	return (0);
}

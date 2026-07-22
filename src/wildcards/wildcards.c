/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:52:15 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/22 18:26:59 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	expand_single_wildcard(t_dynstrarr *w_args, const char *arg);
static int	ft_fnmatch_minishell(const char *pattern, const char *arg);
static int	ft_strarr_apnd(t_dynstrarr *w_args, const char *arg);
static void ft_strarr_sort_range(char **args, size_t start);

/*
** Expands wildcard patterns in the argv array.
** The command name (argv[0]) is kept unchanged.
** Every argument containing '*' is expanded into matching filenames.
** Arguments without wildcards are copied as-is.
** If no match is found, the original pattern is preserved.
*/
int expand_wildcards(char ***args)
{
	size_t		i;
	t_dynstrarr	w_args;
	size_t		start;

	if (!args || !*args || !(*args)[0])
		return (0);
	i = 0;
	ft_memset(&w_args, 0 , sizeof(w_args));
	if (ft_strarr_apnd(&w_args, (*args)[i++]) == 1)
		return (1);
	while ((*args)[i])
	{
		if (!ft_strchr((*args)[i], '*'))
		{
			if (ft_strarr_apnd(&w_args, (*args)[i]) == 1)
				return (1);
		}
		else
		{
			start = w_args.size;
			if (expand_single_wildcard(&w_args, (*args)[i]) == 1)
				return (1);
			ft_strarr_sort_range(w_args.strarr, start);
		}
		i++;
	}
	if (!w_args.strarr)
		return (1);
	ft_strarr_free(*args);
	(*args) = w_args.strarr;
	return (0);
}

/*
** Expands a single wildcard pattern.
** Scans the current directory and appends every matching filename
** to the destination array. Hidden files are ignored unless the
** pattern starts with '.'. If no match is found, the original
** pattern is appended unchanged.
*/
static int expand_single_wildcard(t_dynstrarr *w_args, const char *arg)
{
	DIR				*dir;
	struct dirent	*entry;
	int				found;

	found = 0;
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
		if (arg[0] != '.' && entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (ft_fnmatch_minishell(arg, entry->d_name) == 0)
		{
			if (ft_strarr_apnd(w_args, entry->d_name) == 1)
				return (1);
			found = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (found == 0)
		if (ft_strarr_apnd(w_args, arg) == 1)
			return (1);
	return (0);
}

/*
** Minimal fnmatch implementation supporting only '*'.
** Returns 0 when the filename matches the pattern,
** and 1 otherwise.
*/
static int ft_fnmatch_minishell(const char *pattern, const char *arg)
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
static int ft_strarr_apnd(t_dynstrarr *w_args, const char *arg)
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
** Sorts a NULL-terminated string array in lexicographical order.
** Used to reproduce Bash's behavior, where wildcard matches are
** returned in alphabetical order.
*/
static void ft_strarr_sort_range(char **args, size_t start)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:52:15 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/24 14:50:15 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	expand_single_wildcard(t_dynstrarr *w_args, const char *arg);
static int	ft_fnmatch_minishell(const char *pattern, const char *arg);
static int	ft_strarr_apnd(t_dynstrarr *w_args, const char *arg);
static void	ft_strarr_sort(char **args);

int	expand_wildcards(char ***args)
{
	size_t			i;
	t_dynstrarr		w_args;

	i = 0;
	ft_memset(&w_args, 0 , sizeof(w_args));
	if (ft_strarr_apnd(&w_args, (*args)[i++]) == 1)
		return (1);
	while ((*args)[i])
	{
		if (expand_single_wildcard(&w_args, (*args)[i]) == 1)
			return (1);
		i++;
	}
	if (!w_args.strarr)
		return (1);
	ft_strarr_free(*args);
	(*args) = w_args.strarr;
	ft_strarr_sort(*args);
	return (0);
}

static int	expand_single_wildcard(t_dynstrarr *w_args, const char *arg)
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

//tested, working
static int	ft_fnmatch_minishell(const char *pattern, const char *arg)
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

//tested, working
static int	ft_strarr_apnd(t_dynstrarr *w_args, const char *arg)
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
//tested 50%
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
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:58:16 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:58:33 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

//include
# include <dirent.h>
# include "minishell.h"

//struct
typedef struct s_dynstrarr
{
	char	**strarr;
	size_t	size;
	size_t	capacity;
}	t_dynstrarr;

//ft
//	wildcards.c
int		expand_wildcards(char ***args);
//	wildcards_utils.c
int		handle_entry(t_dynstrarr *w_args, const char *arg,
			struct dirent *entry);
int		ft_fnmatch_minishell(const char *pattern, const char *arg);
int		ft_strarr_apnd(t_dynstrarr *w_args, const char *arg);
void	ft_strarr_sort_range(char **args, size_t start);

#endif
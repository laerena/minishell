/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:57:05 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/14 14:07:10 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_strarr_putendl_fd(char **strarr, int fd);

int	builtin_env(char **envp)
{
	return(ft_strarr_putendl_fd(envp, 1));
}

static int	ft_strarr_putendl_fd(char **strarr, int fd)
{
	while (*strarr)
	{
		if (ft_strchr(*strarr, '='))
			if (ft_putendl_fd(*strarr, fd) == -1)
				return (-1);
		strarr++;
	}
	return (0);
}

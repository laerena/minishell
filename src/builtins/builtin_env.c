/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:57:05 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/26 17:10:44 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(char **envp)
{
	while (*envp)
	{
		if (ft_printf("%s\n", *envp) == -1)
			return (1);
		envp++;
	}
	return (0);
}

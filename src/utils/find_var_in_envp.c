/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_in_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:23:37 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 18:17:26 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**find_var_in_envp(char **envp, char *arg)
{
	size_t	name_len;

	if (!envp || !arg)
		return (NULL);
	name_len = ft_strclen(arg, '=');
	while (*envp)
	{
		if (ft_strclen(*envp, '=') == name_len
			&& ft_strncmp(*envp, arg, name_len) == 0)
			return (envp);
		envp++;
	}
	return (NULL);
}

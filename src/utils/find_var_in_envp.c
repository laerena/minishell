/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_in_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:23:37 by vabisco           #+#    #+#             */
/*   Updated: 2026/06/15 15:23:48 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**find_var_in_envp(char **envp, char *args)
{
	size_t	name_len;

	if (!envp || !args)
		return (NULL);
	name_len = ft_strclen(args, '=');
	while (*envp)
	{
		if (ft_strncmp(*envp, args, name_len) == 0 && (name_len - ft_strclen(*envp, '=') == 0))
			return (envp);
		envp++;
	}
	return (envp);
}

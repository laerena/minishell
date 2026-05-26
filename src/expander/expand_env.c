/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:08:45 by leilai            #+#    #+#             */
/*   Updated: 2026/05/25 17:12:30 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	key_match(char *env, char *key)
{
	int	i;

	i = 0;
	while (key[i] && env[i] && key[i] == env[i])
		i++;
	if (key[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

char	*expand_getenv(char **envp, char *key)
{
	int	i;

	if (!envp || !key)
		return ("");
	i = 0;
	while (envp[i])
	{
		if (key_match(envp[i], key))
			return (envp[i] + ft_strlen(key) + 1);
		i++;
	}
	return ("");
}

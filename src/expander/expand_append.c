/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:25:16 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 15:25:48 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*append_char(char *res, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(res);
	new = malloc(len + 2);
	if (!new)
	{
		free(res);
		return (NULL);
	}
	ft_memcpy(new, res, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(res);
	return (new);
}

char	*append_str(char *res, char *add)
{
	char	*new;
	int		len1;
	int		len2;

	if (!add)
		add = "";
	len1 = ft_strlen(res);
	len2 = ft_strlen(add);
	new = malloc(len1 + len2 + 1);
	if (!new)
	{
		free(res);
		return (NULL);
	}
	ft_memcpy(new, res, len1);
	ft_memcpy(new + len1, add, len2);
	new[len1 + len2] = '\0';
	free(res);
	return (new);
}

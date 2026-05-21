/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:53:05 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/09 21:49:30 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_total_len(int size, char **strs, char *sep)
{
	int	i;
	int	total_len;

	i = 0;
	total_len = ft_strlen(sep) * (size - 1);
	while (i < size)
	{
		if (strs[i])
			total_len += ft_strlen(strs[i]);
		i++;
	}
	return (total_len);
}

void	joiner(char *output, int size, char **strs, char *sep)
{
	int	i;
	int	total_len;

	i = 0;
	total_len = get_total_len(size, strs, sep) + 1;
	while (i < size)
	{
		if (strs[i])
			ft_strlcat(output, strs[i], total_len);
		if (*sep && i < size - 1)
			ft_strlcat(output, sep, total_len);
		i++;
	}
}

char	*ft_strjoin2(int size, char **strs, char *sep)
{
	char	*joined_str;
	int		total_len;

	if (size == 0)
	{
		joined_str = malloc(1);
		if (!joined_str)
			return (NULL);
		joined_str[0] = '\0';
		return (joined_str);
	}
	total_len = get_total_len(size, strs, sep);
	joined_str = malloc(total_len + 1);
	if (!joined_str)
		return (NULL);
	joined_str[0] = '\0';
	joiner(joined_str, size, strs, sep);
	return (joined_str);
}

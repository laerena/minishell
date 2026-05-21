/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:22 by vbunix            #+#    #+#             */
/*   Updated: 2025/10/13 17:41:30 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	start;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	while (s1_len > 0 && ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	while (s1_len > start && ft_strchr(set, s1[start]))
		start++;
	s1_len -= start;
	return (ft_substr(s1, start, s1_len));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:11:15 by vbunix            #+#    #+#             */
/*   Updated: 2025/10/13 18:53:21 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t			count;
	unsigned int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_split(char **out)
{
	char	**tmp;

	tmp = out;
	while (*out)
		free(*out++);
	free(tmp);
}

static char	**splitter(char **out, char const *s, char c, size_t w_count)
{
	size_t	array;
	size_t	i;

	array = 0;
	while (array < w_count)
	{
		i = 0;
		while (*s == c)
			s++;
		while (s[i] && s[i] != c)
			i++;
		out[array] = ft_substr(s, 0, i);
		if (!out[array])
			return (free_split(out), NULL);
		array++;
		s += i;
	}
	return (out);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	size_t	w_count;

	if (!s)
		return (NULL);
	w_count = word_count(s, c);
	out = malloc(sizeof(char *) * (w_count + 1));
	if (!out)
		return (NULL);
	out[w_count] = NULL;
	return (splitter(out, s, c, w_count));
}

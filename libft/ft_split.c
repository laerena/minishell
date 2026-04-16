/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:57:17 by leilai            #+#    #+#             */
/*   Updated: 2025/10/29 15:57:19 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *str, char c);
static char	*ft_wfill(const char *str, int st, int end);
static void	*ft_free(char **strs, int count);
static void	ft_initi(size_t *i, int *j, int *sw);

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	i;
	int		j;
	int		sw;

	ft_initi(&i, &j, &sw);
	result = ft_calloc((ft_wcount(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && sw < 0)
			sw = i;
		else if ((s[i] == c || i == ft_strlen(s)) && sw >= 0)
		{
			result[j] = ft_wfill(s, sw, i);
			if (!(result[j]))
				return (ft_free(result, j));
			sw = -1;
			j++;
		}
		i++;
	}
	return (result);
}

static void	ft_initi(size_t *i, int *j, int *sw)
{
	*i = 0;
	*j = 0;
	*sw = -1;
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static char	*ft_wfill(const char *str, int st, int end)
{
	char	*w;
	int		i;

	i = 0;
	w = malloc((end - st + 1) * sizeof(char));
	if (!w)
		return (NULL);
	while (st < end)
	{
		w[i] = str[st];
		i++;
		st++;
	}
	w[i] = '\0';
	return (w);
}

static int	ft_wcount(const char *str, char c)
{
	int	count;
	int	w;

	count = 0;
	w = 0;
	while (*str)
	{
		if (*str != c && w == 0)
		{
			w = 1;
			count++;
		}
		else if (*str == c)
			w = 0;
		str++;
	}
	return (count);
}

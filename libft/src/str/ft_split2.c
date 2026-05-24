/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:18:58 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/24 11:17:19 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static int	is_sep(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}

static int	count_str(char *str, char *charset)
{
	int	count;
	int	in_word;

	if (!*charset && *str)
		return (1);
	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_sep(*str, charset))
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*extract_str(char *start, int len)
{
	char	*output;
	int		i;

	i = 0;
	output = malloc((len + 1));
	if (!output)
		return (NULL);
	output[len] = '\0';
	while (i < len)
	{
		output[i] = start[i];
		i++;
	}
	return (output);
}

static void	splitter(char **output, char *str, char *charset, int str_nbr)
{
	char	*start;
	int		i;

	i = 0;
	while (i < str_nbr)
	{
		while (is_sep(*str, charset))
			str++;
		start = str;
		while (!is_sep(*str, charset) && *str)
			str++;
		output[i++] = extract_str(start, str - start);
	}
	return ;
}

char	**ft_split2(char *str, char *charset)
{
	char	**output;
	int		str_nbrs;

	if (!str || !charset)
		return (NULL);
	str_nbrs = count_str(str, charset);
	output = malloc(sizeof(char *) * (str_nbrs + 1));
	if (!output)
		return (NULL);
	output[str_nbrs] = NULL;
	splitter(output, str, charset, str_nbrs);
	return (output);
}

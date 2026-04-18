/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:55:45 by leilai            #+#    #+#             */
/*   Updated: 2026/04/18 15:59:16 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*find_last_pipe(t_token *start, t_token *end)
{
	t_token	*last_pipe;

	last_pipe = NULL;
	while (start && start != end)
	{
		if (start->type == T_PIPE)
			last_pipe = start;
		start = start->next;
	}
	return (last_pipe);
}

static int	count_words(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start && start != end)
	{
		if (start->type == T_WORD)
			count++;
		start = start->next;
	}
	return (count);
}

static void	free_partial_av(char **av, int used)
{
	while (used > 0)
		free(av[--used]);
	free(av);
}

/* 
** build av from WORD tokens
** ast owns its own copies of command strings 
** later token list and ast freed seperately
*/
char	**tokens_to_av(t_token *start, t_token *end)
{
	char	**av;
	int		i;

	av = malloc(sizeof(char *) * (count_words(start, end) + 1));
	if (!av)
		return (NULL);
	i = 0;
	while (start && start != end)
	{
		if (start->type == T_WORD)
		{
			av[i] = ft_strdup(start->value);
			if (!av[i])
				return (free_partial_av(av, i), NULL);
			i++;
		}
		start = start->next;
	}
	av[i] = NULL;
	return (av);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:55:45 by leilai            #+#    #+#             */
/*   Updated: 2026/05/23 14:31:36 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*find_last_top_level(t_token *start, t_token *end, t_token_type type)
{
	t_token	*last;
	int		depth;

	last = NULL;
	depth = 0;
	while (start && start != end)
	{
		if (start->type == T_LPAREN)
			depth++;
		else if (start->type == T_RPAREN)
			depth--;
		else if (depth == 0 && start->type == type)
			last = start;
		start = start->next;
	}
	return (last);
}

static int	count_words(t_token *start, t_token *end)
{
	int	count;

	count = 0;
	while (start && start != end)
	{
		if (is_redirection(start->type))
		{
			if (start->next && start->next != end)
				start = start->next;
		}
		else if (start->type == T_WORD)
			count++;
		start = start->next;
	}
	return (count);
}

static void	free_partial_argv(char **argv, int used)
{
	while (used > 0)
		free(argv[--used]);
	free(argv);
}

/* 
** build argv from WORD tokens
** ast owns its own copies of command strings 
** later token list and ast freed seperately
*/
char	**tokens_to_argv(t_token *start, t_token *end)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (count_words(start, end) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (start && start != end)
	{
		if (is_redirection(start->type))
		{
			if (start->next && start->next != end)
				start = start->next;
		}
		else if (start->type == T_WORD)
		{
			argv[i] = ft_strdup(start->value);
			if (!argv[i])
				return (free_partial_argv(argv, i), NULL);
			i++;
		}
		start = start->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	is_builtin_cmd(char *cmd_name)
{
	size_t		i;
	size_t		builtin_len;
	static char	*builtincmds[] = {
		"cd", "echo", "export", "unset", "env", "exit", "pwd",
		NULL
	};

	i = 0;
	while (builtincmds[i])
	{
		builtin_len = ft_strlen(builtincmds[i]) + 1;
		if (ft_strncmp(builtincmds[i], cmd_name, builtin_len) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

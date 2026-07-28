/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:31:49 by leilai            #+#    #+#             */
/*   Updated: 2026/07/28 18:28:35 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*append_status(t_ctx *ctx, int *i, char *res)
{
	char	*status;

	status = ft_itoa(ctx->last_exit_status);
	if (!status)
	{
		free(res);
		return (NULL);
	}
	res = append_str(res, status);
	free(status);
	(*i)++;
	return (res);
}

static char	*expand_var(t_ctx *ctx, char *s, int *i, char *res)
{
	int		start;
	char	*key;
	char	*value;

	(*i)++;
	if (s[*i] == '?')
		return (append_status(ctx, i, res));
	start = *i;
	while (is_var_char(s[*i]))
		(*i)++;
	if (start == *i)
		return (append_char(res, '$'));
	key = ft_substr(s, start, *i - start);
	if (!key)
		return (free(res), NULL);
	value = expand_getenv(ctx->envp, key);
	res = append_str(res, value);
	free(key);
	return (res);
}

char	*expand_str(t_ctx *ctx, char *s)
{
	char	*res;
	int		i;
	char	quote;

	if (!s)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	quote = 0;
	while (s[i])
	{
		if (handle_quote(s[i], &quote))
			res = append_char(res, s[i++]);
		else if (s[i] == '$' && quote != '\'')
			res = expand_var(ctx, s, &i, res);
		else
			res = append_char(res, s[i++]);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	expand_argv(t_ctx *ctx, char **argv)
{
	int		i;
	char	*new;

	i = 0;
	while (argv && argv[i])
	{
		new = expand_str(ctx, argv[i]);
		if (!new)
			return (1);
		free(argv[i]);
		argv[i] = new;
		i++;
	}
	return (0);
}

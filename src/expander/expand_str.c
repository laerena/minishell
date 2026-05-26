/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:31:49 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 08:45:14 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*append_char(char *res, char c)
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

static char	*append_str(char *res, char *add)
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
	{
		free(res);
		return (NULL);
	}
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
		if ((s[i] == '\'' || s[i] == '"') && quote == 0)
			quote = s[i++];
		else if (s[i] == quote)
		{
			quote = 0;
			i++;
		}
		if (s[i] == '$' && quote != '\'')
			res = expand_var(ctx, s, &i, res);
		else
		{
			res = append_char(res, s[i]);
			i++;
		}
		if (!res)
			return (NULL);
	}
	return (res);
}

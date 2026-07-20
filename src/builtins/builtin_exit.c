/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:50:52 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/20 15:46:45 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "utils.h"

static int	get_exit_code(long long value);

void	builtin_exit(t_ctx *ctx, char **argv)
{
	long long	value;
	char		*end;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[0])
		exit_clean(ctx, ctx->last_exit_status);
	errno = 0;
	value = ft_strtoll(argv[0], &end, 10);
	if (errno == ERANGE || end == argv[0] || *end != '\0')
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit_clean(ctx, 2);
	}
	if (argv[1])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		ctx->last_exit_status = 1;
		return ;
	}
	exit_clean(ctx, get_exit_code(value));
}

static int	get_exit_code(long long value)
{
	int	exit_code;
	
	exit_code = value % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (exit_code);
}

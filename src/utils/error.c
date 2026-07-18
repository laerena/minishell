/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:40:43 by leilai            #+#    #+#             */
/*   Updated: 2026/07/18 14:43:04 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "struct.h"

int	syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	malloc_error(void)
{
	ft_putstr_fd("minishell: malloc error\n", 2);
	return (1);
}

int	print_syntax_error(char *msg)
{
	return (syntax_error(msg));
}

/*
Update ctx->last_exit_status to the code
Transmit the msg to perror
Return the code
*/
int	fail(t_ctx *ctx, int code, char *msg)
{
	if (msg)
		perror(msg);
	ctx->last_exit_status = code;
	return (code);
}

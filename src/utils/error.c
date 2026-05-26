/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:40:43 by leilai            #+#    #+#             */
/*   Updated: 2026/05/26 14:57:57 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:47:29 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:47:30 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../libft/include/libft.h"
# include <unistd.h>
# include "struct.h"
# include <stdio.h>

int	syntax_error(char *msg);
int	malloc_error(void);
int	print_syntax_error(char *msg);
int	fail(t_ctx *ctx, int code, char *msg);

#endif
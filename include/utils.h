/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:57:03 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:58:01 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_split(char **arr);

void	print_tokens(t_token *tokens);
void	print_ast(t_cmd *cmd);

char	**find_var_in_envp(char **envp, char *args);

int		my_dup2(int oldfd, int newfd);

void	malloc_error_exit(t_ctx *ctx);
void	ctx_cleanup(t_ctx *ctx);
void	exit_clean(t_ctx *ctx, int exit_code);

#endif
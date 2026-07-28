/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:47:18 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 18:47:19 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//include
# include "minishell.h"
# include "executor.h"

//fts
int		builtin_echo(t_ctx *ctx, char **args);
int		builtin_cd(t_ctx *ctx, char **args);
int		builtin_pwd(t_ctx *ctx);
int		builtin_env(t_ctx *ctx, t_execmd *cmd, char **envp);
int		builtin_export(t_ctx *ctx, char **args);
int		export_p(char **envp);
int		builtin_unset(t_ctx *ctx, char **args);
void	builtin_exit(t_ctx *ctx, char **argv);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:49:02 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/23 19:20:31 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**extract_paths_from_envp(char **envp);
static char	*exec_path_finder(char *cmd, char **dirs_path);

int	run_exec(t_ctx *ctx, t_cmd *ast_node)
{
	char	**args;
	char	*exec_path;
	char	**dirs_path;
	
	args = ast_node->u_cmd.exec.argv;
	if (!args || !args[0])
		return (ctx->last_exit_status = 1, 1);
	dirs_path = extract_paths_from_envp(ctx->envp);
	exec_path = exec_path_finder(args[0], dirs_path);
	if (!exec_path)
	{
		ft_eprintf("%s: command not found\n", args[0]);
		return (ctx->last_exit_status = 1, 1);
	}
	if (expand_wildcards(&args) == 1)
		return (ctx->last_exit_status = 1, 1);
	if (execve(exec_path, args, ctx->envp) == -1)
	{
		perror("execve");
		return (ctx->last_exit_status = 1, 1);
	}
	free(exec_path);
	ft_strarr_free(dirs_path);
	return (ctx->last_exit_status = 0, 0);
}

static char	**extract_paths_from_envp(char **envp)
{
	char	*path;

	path = NULL;
	while(*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			path = *envp;
		envp++;
	}
	if (!path)
		return (NULL);
	return(ft_split((path + 5), ':'));
}

static char	*exec_path_finder(char *cmd, char **dirs_path)
{
	char	*exec_path;
	char	**dirs_iter;

	exec_path = NULL;
	if (!dirs_path)
		return (NULL);
	dirs_iter = dirs_path;
	while (*dirs_iter)
	{
		ft_asprintf(&exec_path, "%s/%s", *dirs_iter, cmd);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		exec_path = NULL;
		dirs_iter++;
	}
	return (exec_path);
}

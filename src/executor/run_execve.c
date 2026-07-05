/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:49:02 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/05 13:50:59 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

static char	**extract_path_from_envp(char **envp);
static char	*exec_path_finder(char *cmd, char **dirs_path);
static int	exec_error(t_ctx *ctx, char *exec_path, char **dirs_path);
static int	exec_not_found(t_ctx *ctx, char *cmd, char **dirs_path);

int	run_execve_wrapper(t_ctx *ctx, t_cmd *exec_node, int no_fork)
{
	(void)no_fork;
	return (run_execve(ctx, &exec_node->u_cmd.exec));
}

int	run_execve(t_ctx *ctx, t_execmd *cmd)
{
	char	**args;
	char	*exec_path;
	char	**dirs_path;

	args = cmd->argv;
	if (!args || !args[0])
		return (ctx->last_exit_status = 0, 0);
	dirs_path = extract_path_from_envp(ctx->envp);
	exec_path = exec_path_finder(args[0], dirs_path);
	if (!exec_path)
		return (exec_not_found(ctx, args[0], dirs_path));
	if (expand_wildcards(&args) == 1)
		return (exec_error(ctx, exec_path, dirs_path));
	if (execve(exec_path, args, ctx->envp) == -1)
	{
		perror("execve");
		return (exec_error(ctx, exec_path, dirs_path));
	}
	free(exec_path);
	ft_strarr_free(dirs_path);
	return (ctx->last_exit_status = 0, 0);
}

static int	exec_not_found(t_ctx *ctx, char *cmd, char **dirs_path)
{
	ft_eprintf("%s: command not found\n", cmd);
	ft_strarr_free(dirs_path);
	ctx->last_exit_status = 1;
	return (1);
}

static int	exec_error(t_ctx *ctx, char *exec_path, char **dirs_path)
{
	free(exec_path);
	ft_strarr_free(dirs_path);
	ctx->last_exit_status = 1;
	return (1);
}

static char	**extract_path_from_envp(char **envp)
{
	char	*path;

	path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			path = *envp;
		envp++;
	}
	if (!path)
		return (NULL);
	return (ft_split((path + 5), ':'));
}

static char	*exec_path_finder(char *cmd, char **dirs_path)
{
	char	*exec_path;
	char	**dirs_iter;
	char	*tmp;

	exec_path = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!dirs_path)
		return (NULL);
	dirs_iter = dirs_path;
	while (*dirs_iter)
	{
		//ft_asprintf(&exec_path, "%s/%s", *dirs_iter, cmc);
		tmp = ft_strjoin(*dirs_iter, "/");
		if (!tmp)
			return (NULL);
		exec_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		exec_path = NULL;
		dirs_iter++;
	}
	return (exec_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:49:02 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/19 15:22:52 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

static char	**extract_path_from_envp(char **envp);
static char	*exec_path_finder(char *cmd, char **dirs_path);
static int	exec_error(t_ctx *ctx, char *exec_path, char **dirs_path);
static int	exec_not_found(t_ctx *ctx, char *cmd, char **dirs_path);
static int	check_exec_path(t_ctx *ctx, char *path);

int	run_execve_wrapper(t_ctx *ctx, t_cmd *exec_node, int no_fork)
{
	(void)no_fork;
	return (run_execve(ctx, &exec_node->u_cmd.exec));
}

//note: if 'unset PATH', exec_path will be NULL and return the wrong error "cmd not found"
int	run_execve(t_ctx *ctx, t_execmd *cmd)
{
	char	*exec_path;
	char	**dirs_path;

	if (!cmd->argv || !cmd->argv[0])
		return (ctx->last_exit_status = 0, 0);
	if (cmd->argv[0][0] == '\0')
		return (exec_not_found(ctx, cmd->argv[0], NULL));
	dirs_path = extract_path_from_envp(ctx->envp);
	exec_path = exec_path_finder(cmd->argv[0], dirs_path);
	if (!exec_path)
		return (exec_not_found(ctx, cmd->argv[0], dirs_path));
	if (check_exec_path(ctx, exec_path))
	{
		free(exec_path);
		ft_strarr_free(dirs_path);
		return (ctx->last_exit_status);
	}
	execve(exec_path, cmd->argv, ctx->envp);
	return (exec_error(ctx, exec_path, dirs_path));
}

static char	**extract_path_from_envp(char **envp)
{
	char	*path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			return (ft_split(path, ':'));
		}
		envp++;
	}
	return (NULL);
}

static char	*exec_path_finder(char *cmd, char **dirs_path)
{
	char	*exec_path;
	char	**dirs_iter;
	char	*tmp;

	exec_path = NULL;
	if (ft_strchr(cmd, '/') || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, "..")
		|| !ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3))
		return (ft_strdup(cmd));
	dirs_iter = dirs_path;
	while (dirs_iter && *dirs_iter)
	{
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

static int	exec_not_found(t_ctx *ctx, char *cmd, char **dirs_path)
{
	ft_eprintf("%s: command not found\n", cmd);
	if (dirs_path)
		ft_strarr_free(dirs_path);
	ctx->last_exit_status = 127;
	return (127);
}

static int	check_exec_path(t_ctx *ctx, char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
	{
		ft_eprintf("%s: Is a directory\n", path);
		ctx->last_exit_status = 126;
		return (1);
	}
	return (0);
}

static int	exec_error(t_ctx *ctx, char *exec_path, char **dirs_path)
{
	int	error;
	int	status;

	error = errno;
	status = 1;
	ft_eprintf("%s: %s\n", exec_path, strerror(error));
	if (error == ENOENT)
		status = 127;
	else if (error == EACCES || error == ENOEXEC)
		status = 126;
	free(exec_path);
	ft_strarr_free(dirs_path);
	ctx->last_exit_status = status;
	return (status);
}

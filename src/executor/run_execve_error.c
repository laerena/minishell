/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:46:00 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 17:50:20 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_exec_path(t_ctx *ctx, char *path)
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

int	exec_not_found(t_ctx *ctx, char *cmd, char **dirs_path)
{
	ft_eprintf("%s: command not found\n", cmd);
	if (dirs_path)
		ft_strarr_free(dirs_path);
	ctx->last_exit_status = 127;
	return (127);
}

int	exec_error(t_ctx *ctx, char *exec_path, char **dirs_path)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 11:51:46 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/28 17:42:00 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	save_target_fd(int target_fd);

int	save_fds(int fd, t_redir_save_fds *saved_fds)
{
	if (fd == STDIN_FILENO
		&& saved_fds->saved_stdin == -1)
	{
		saved_fds->saved_stdin = save_target_fd(STDIN_FILENO);
		if (saved_fds->saved_stdin == -1)
			return (1);
	}
	if (fd == STDOUT_FILENO
		&& saved_fds->saved_stdout == -1)
	{
		saved_fds->saved_stdout = save_target_fd(STDOUT_FILENO);
		if (saved_fds->saved_stdout == -1)
			return (1);
	}
	return (0);
}

static int	save_target_fd(int target_fd)
{
	int	saved_fd;

	saved_fd = dup(target_fd);
	if (saved_fd < 0)
	{
		perror("dup: save_target_fd");
		return (-1);
	}
	return (saved_fd);
}

int	redirect_fd(int file_fd, int target_fd)
{
	if (file_fd == target_fd)
		return (0);
	if (dup2(file_fd, target_fd) == -1)
	{
		perror("dup2");
		close(file_fd);
		return (-1);
	}
	close(file_fd);
	return (0);
}

int	restore_fds(t_redir_save_fds *saved_fds)
{
	int	ret;

	ret = 0;
	if (saved_fds->saved_stdin != -1)
	{
		if (dup2(saved_fds->saved_stdin, STDIN_FILENO) == -1)
			ret = -1;
		close(saved_fds->saved_stdin);
		saved_fds->saved_stdin = -1;
	}
	if (saved_fds->saved_stdout != -1)
	{
		if (dup2(saved_fds->saved_stdout, STDOUT_FILENO) == -1)
			ret = -1;
		close(saved_fds->saved_stdout);
		saved_fds->saved_stdout = -1;
	}
	if (ret == -1)
		perror("dup2: restore_fds");
	return (ret);
}

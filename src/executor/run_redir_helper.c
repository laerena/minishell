/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <leilai@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 11:51:46 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/03 14:46:39 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	save_target_fd(int target_fd)
{
	int	saved_fd;

	saved_fd = dup(target_fd);
	if (saved_fd < 0)
	{
		perror("dup");
		return (-1);
	}
	return (saved_fd);
}

int	redirect_fd(int file_fd, int target_fd)
{
	if (dup2(file_fd, target_fd) == -1)
	{
		perror("dup2");
		close(file_fd);
		return (-1);
	}
	close(file_fd);
	return (0);
}

int	restore_saved_fd(int saved_fd, int target_fd)
{
	if (dup2(saved_fd, target_fd) == -1)
	{
		perror("dup2 restore");
		close(saved_fd);
		return (1);
	}
	close(saved_fd);
	return (0);
}

int	save_redir_fds(int saved[2])
{
	saved[0] = save_target_fd(STDIN_FILENO);
	if (saved[0] < 0)
		return (1);
	saved[1] = save_target_fd(STDOUT_FILENO);
	if (saved[1] < 0)
	{
		close(saved[0]);
		return (1);
	}
	return (0);
}

int	restore_redir_fds(int saved[2])
{
	if (restore_saved_fd(saved[0], STDIN_FILENO) == 1)
		return (1);
	if (restore_saved_fd(saved[1], STDOUT_FILENO) == 1)
		return (1);
	return (0);
}

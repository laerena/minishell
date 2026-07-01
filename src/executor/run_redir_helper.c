/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 11:51:46 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/01 13:23:34 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int save_target_fd(int target_fd)
{
	int saved_fd;

	saved_fd = dup(target_fd);
	if (saved_fd < 0)
	{
		perror("dup");
		return (-1);
	}
	return (saved_fd);
}

int redirect_fd(int file_fd, int target_fd)
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

int restore_saved_fd(int saved_fd, int target_fd)
{
	if (dup2(saved_fd, target_fd) == -1)
	{
		return (perror("dup2 restore"), 1);
		close(saved_fd);
		return (1);
	}
	close(saved_fd);
	return (0);
}

//!\ If oldfd == newfd, dup2 is a no-op; do not close oldfd (that would close the target).
// int my_dup2(int oldfd, int newfd)
// {
// 	if (oldfd == newfd)
// 		return (0);
// 	if (dup2(oldfd, newfd) < 0)
// 	{
// 		perror("dup2");
// 		close(oldfd);
// 		return (1);
// 	}
// 	close(oldfd);
// 	return (0);
// }

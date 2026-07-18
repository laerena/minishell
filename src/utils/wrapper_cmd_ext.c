/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_cmd_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:53:10 by vabisco           #+#    #+#             */
/*   Updated: 2026/07/18 15:03:47 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int 	my_dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (0);
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:56:48 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/05 16:56:48 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl_node	*gnl_get_and_create_node(int fd, t_gnl_node **bucket)
{
	t_gnl_node	*new_node;
	t_gnl_node	*prev;

	if (!bucket)
		return (NULL);
	prev = *bucket;
	if (*bucket)
	{
		if ((*bucket)->fd == fd)
			return (*bucket);
		while (prev->next && prev->next->fd != fd)
			prev = prev->next;
		if (prev->next && prev->next->fd == fd)
			return (prev->next);
	}
	new_node = malloc(sizeof(t_gnl_node));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = NULL;
	new_node->next = NULL;
	if (!*bucket)
		return (*bucket = new_node);
	else
		return (prev->next = new_node);
}

static int	gnl_read(int fd, t_gnl_node *node)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*tmpstash;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!node->stash || !ft_strchr(node->stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), -1);
		if (bytes_read == 0)
			return (free(buffer), 0);
		buffer[bytes_read] = '\0';
		tmpstash = ft_strjoin(node->stash, buffer);
		if (!tmpstash)
			return (free(buffer), -1);
		free(node->stash);
		node->stash = tmpstash;
	}
	return (free(buffer), 1);
}

static char	*gnl_extract_line(t_gnl_node *node)
{
	char	*line;
	char	*tmpstash;
	size_t	eol;

	if (!node->stash || !*node->stash)
		return (NULL);
	eol = ft_strclen(node->stash, '\n');
	if (node->stash[eol] == '\n')
		eol++;
	line = malloc(eol + 1);
	if (!line)
		return (NULL);
	line[eol] = '\0';
	tmpstash = ft_strdup(&node->stash[eol]);
	if (!tmpstash)
		return (free(line), NULL);
	line = ft_memcpy(line, node->stash, eol);
	free(node->stash);
	node->stash = tmpstash;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl_node	*hashtable[HASHTABLE_SIZE];
	t_gnl_node			*node;
	int					read_check;
	size_t				index;
	char				*line;

	if (fd == -1)
		gnl_full_cleanup(hashtable);
	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	index = fd % HASHTABLE_SIZE;
	node = gnl_get_and_create_node(fd, &hashtable[index]);
	if (!node)
		return (NULL);
	read_check = gnl_read(fd, node);
	if (read_check == -1)
		return (gnl_cleanup(&hashtable[index], node), NULL);
	line = gnl_extract_line(node);
	if (!line)
		return (gnl_cleanup(&hashtable[index], node), NULL);
	if (!node->stash && read_check == 0)
		return (gnl_cleanup(&hashtable[index], node), NULL);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:03:22 by vabisco           #+#    #+#             */
/*   Updated: 2025/11/05 17:03:22 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Define
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef HASHTABLE_SIZE
#  define HASHTABLE_SIZE 256
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

// Include
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

// Struct
typedef struct s_node
{
	int				fd;
	char			*stash;
	struct s_node	*next;
}	t_gnl_node;

// FT
//  get_next_line.c
char	*get_next_line(int fd);
void	gnl_full_cleanup(t_gnl_node **hashtable);
void	gnl_cleanup(t_gnl_node **bucket, t_gnl_node *node);

#endif

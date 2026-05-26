/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:21:00 by vabisco           #+#    #+#             */
/*   Updated: 2026/05/25 16:26:22 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//convert ptr index into a size_t index
size_t	ft_ptr_index(const void *base, const void *ptr)
{
	return ((size_t)((const char *)ptr - (const char *)base));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:36:30 by vabisco           #+#    #+#             */
/*   Updated: 2025/10/14 16:36:30 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current_lst;
	t_list	*new_lst;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	current_lst = lst;
	while (current_lst)
	{
		new_node = ft_lstnew(f(current_lst->content));
		if (!new_node)
			return (ft_lstclear(&new_lst, del), NULL);
		ft_lstadd_back(&new_lst, new_node);
		current_lst = current_lst->next;
	}
	return (new_lst);
}

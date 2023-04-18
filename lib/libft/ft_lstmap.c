/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:53:34 by jgo               #+#    #+#             */
/*   Updated: 2022/11/17 11:05:11 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*del_lst(void *new_item, t_list *new_list, void (*del)(void*));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new_lst;
	t_list	*node;
	void	*new_item;

	if (!lst || !f)
		return ((void *)0);
	new_item = f(lst->content);
	new_lst = ft_lstnew(new_item);
	if (!new_lst)
		return (del_lst(new_item, new_lst, del));
	node = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		new_item = f(lst->content);
		node->next = ft_lstnew(new_item);
		if (!node->next)
			return (del_lst(new_item, new_lst, del));
		node = node->next;
	}
	return (new_lst);
}

static t_list	*del_lst(void *new_item, t_list *new_lst, void (*del)(void*))
{
	del(new_item);
	ft_lstclear(&new_lst, del);
	return ((void *)0);
}

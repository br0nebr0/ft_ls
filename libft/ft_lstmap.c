/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:15:08 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/10 21:17:18 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freelist(t_list **list)
{
	if (list)
	{
		if ((*list)->next)
			ft_freelist(&((*list)->next));
		if (*list)
		{
			free((*list)->content);
			(*list)->content_size = 0;
			free(*list);
			*list = NULL;
		}
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list;
	t_list *buf;

	if (!lst || !f)
		return (NULL);
	list = f(lst);
	buf = list;
	while (lst->next)
	{
		lst = lst->next;
		if (!(list->next = f(lst)))
		{
			ft_freelist(&buf);
			return (NULL);
		}
		list = list->next;
	}
	return (buf);
}

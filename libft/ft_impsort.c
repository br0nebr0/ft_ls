#include "libft.h"

static void splitlist(t_imp *source, t_imp **lst1, t_imp **lst2, int size)
{
	int i;

	i = 0;
	*lst2 = source;
	while (i < size / 2)
	{
		*lst1 = *lst2;
		*lst2 = (*lst2)->next;
		i++;
	}
	(*lst1)->next = NULL;
	*lst1 = source;
}

static t_imp *addlink(t_imp *list, t_imp **lst)
{
	t_imp *buf;

	if (!list)
	{
		buf = *lst;
		*lst = (*lst)->next;
		buf->next = NULL;
		list = buf;
		return(list);
	}
	buf = list;
	while (list->next)
		list = list->next;
	list->next = *lst;
	*lst = (*lst)->next;
	list->next->next = NULL;
	list = buf;
	return (list);
}

static t_imp *addtail(t_imp *list, t_imp **lst)
{
	t_imp *buf;

	buf = list;
	while (list->next)
		list = list->next;
	list->next = *lst;
	list = buf;
	*lst = NULL;
	return (list);
}

static t_imp *mergelist(t_imp *lst1, t_imp *lst2, int (*compr)(void *, void *))
{
	t_imp *lst;

	lst = NULL;
	while (lst1 || lst2)
	{
		if (lst1 && lst2)
		{
			if (compr(lst1->content, lst2->content) > 0)
				lst = addlink(lst, &lst2);
			else
				lst = addlink(lst, &lst1);
		}
		if (lst1 && !lst2)
			lst = addtail(lst, &lst1);
		if (!lst1 && lst2)
			lst = addtail(lst, &lst2);
	}
	return (lst);
}

t_imp *ft_impsort(t_imp *lst, int cnt, int (*compr)(void *, void *))
{
	t_imp	*l_lst;
	t_imp	*r_lst;
	t_imp	*n_lst;

	if (cnt < 2)
	{
		n_lst = lst;
		return(n_lst);
	}
	splitlist(lst, &l_lst, &r_lst, cnt);
	l_lst = ft_impsort(l_lst, cnt / 2, compr);
	r_lst = ft_impsort(r_lst, cnt - cnt / 2, compr);
	n_lst = mergelist(l_lst, r_lst, compr);
	return (n_lst);
}

#include "ft_ls.h"

int s_ls(void *lst1, void *lst2)
{
	t_file *el1;
	t_file *el2;

	el1 = (t_file *) lst1;
	el2 = (t_file *) lst2;
	if (el2->ls.tv_sec - el1->ls.tv_sec > 0)
		return (1);
	return (0);
}

int s_la(void *lst1, void *lst2)
{
	t_file *el1;
	t_file *el2;

	el1 = (t_file *) lst1;
	el2 = (t_file *) lst2;
	if (el2->la.tv_sec - el1->la.tv_sec > 0)
		return (1);
	return (0);
}

int s_lm(void *lst1, void *lst2)
{
	t_file *el1;
	t_file *el2;

	el1 = (t_file *) lst1;
	el2 = (t_file *) lst2;
	if (el2->lm.tv_sec - el1->lm.tv_sec > 0)
		return (1);
	return (0);
}
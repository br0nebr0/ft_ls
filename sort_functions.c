#include "ft_ls.h"

/*sort by name on t_file*/
int s_name(void *lst1, void *lst2)
{
	t_file *el1;
	t_file *el2;

	el1 = (t_file *) lst1;
	el2 = (t_file *) lst2;

	if (ft_strcmp(el1->name, el2->name) > 0)
		return (1);
	return (0);
}

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

int s_nm(void *str1, void *str2)
{
	char *el1;
	char *el2;

	el1 = (char *) str1;
	el2 = (char *) str2;

	if (ft_strcmp(el1, el2) > 0)
		return (1);
	return (0);
}
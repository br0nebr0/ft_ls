#include "libft.h"

t_imp *ft_imprev(t_imp *list)
{
	t_imp *prev;
	t_imp *cur;
	t_imp *next;

	cur = list;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next; 
	}
	return (prev);
}
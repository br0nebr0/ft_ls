#include "libft.h"

int ft_impsize(t_imp *lst)
{
	int		i;
	t_imp	*buf;

	i = 0;
	buf = lst;
	while (buf)
	{
		buf = buf->next;
		i++;
	}
	return(i);
}

#include "libft.h"

void	ft_impdellist(t_imp **imp, void (*del)(void **))
{
	if (imp)
	{
		while (*imp)
			ft_impdel(&(*imp), del);
	}
}
#include "ft_ls.h"

int find(char *str1, char *str2)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(str2);
	while(i < j)
	{
		if (ft_strchr(str1, str2[i]))
			return (1);
		i++;
	}
	return (0);
}

void sort_by_flags(t_imp **list, char *flags)
{
	if (!ft_strchr(flags, 'f'))
		*list = ft_impsort(*list, ft_impsz(*list), s_name);
	if (ft_strchr(flags, 'c') && !find(flags, ""))
		*list = ft_impsort(*list, ft_impsz(*list), s_ls);
	if (ft_strchr(flags, 't'))
		*list = ft_impsort(*list, ft_impsz(*list), s_lm);
	if (ft_strchr(flags, 'S'))
		*list = ft_impsort(*list, ft_impsz(*list), s_la);
	if (ft_strchr(flags, 'r'))
		*list = ft_imprev(*list);
}

void printwspaces(int sz)
{
	int i;

	i = 0;
	while (i < sz)
	{
		ft_putchar(' ');
		i++;
	}
}

void printword(char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
}

void printnum(int nbr)
{
	ft_putnbr(nbr);
	ft_putchar(' ');
}

#include "ft_ls.h"

int ch_nbr_sz(int size, long long int nbr)
{
	int str;

	str = 0;
	while (nbr > 0)
	{
		str++;
		nbr /= 10;
	}
	if (str > size)
		size = str;
	return (size);
}

int ch_str_sz(int size, char *str)
{
	if ((int) ft_strlen(str) > size)
		size = ft_strlen(str);
	return (size);
}

int *get_sizes(t_imp *list, char *flags)
{
	int *sz;
	t_file *stat;

	sz = (int *) ft_memalloc(sizeof(int) * 5);
	while (list)
	{
		stat = (t_file *) list->content;
		sz[0] = ch_nbr_sz(sz[0], stat->blk / ((ft_strchr(flags, 's')) ? 2 : 1));
		sz[1] = ch_nbr_sz(sz[1], stat->lnk);
		sz[2] = ft_strchr(flags, 'n') ? ch_nbr_sz(sz[2], getpwuid(stat->usr)->pw_uid)
		: ch_str_sz(sz[2], getpwuid(stat->usr)->pw_name);
		sz[3] = ft_strchr(flags, 'n') ? ch_nbr_sz(sz[3], getgrgid(stat->usr)->gr_gid)
		: ch_str_sz(sz[3], getgrgid(stat->usr)->gr_name);
		sz[4] = ch_nbr_sz(sz[4], stat->size);			
		list = list->next;
	}
	return (sz);
}

void out(t_imp **params, char *flags, int *size, char *path)
{
	t_imp *lst;
	t_file *buf;

	lst = *params;
	buf = (t_file *) (lst->content);
		if(ft_strchr(flags, 'a'))
			printdirs(buf, flags, size, path);
		else 
		{
			if (ft_strchr(flags, 'A') && (!ft_strequ(buf->name, "..") && !ft_strequ(buf->name, ".")))
			printdirs(buf, flags, size, path);
			else if (((buf->name)[0] == '.' || (buf->name)[0] != '~') && ft_strchr(flags, 'd'))
				printdirs(buf, flags, size, path);
			else if ((buf->name)[0] != '.' && (buf->name)[0] != '~')
				printdirs(buf, flags, size, path);
		}
}

void output(t_imp **params, char *flags, int sum, char *path)
{
	t_imp *lst;
	int		*size;

	lst = *params;
	size = NULL;
	if (find(flags, "longks"))
	{
	size = get_sizes(lst, flags);
		if (sum >= 0)
		{
			ft_putstr("total: ");
			if (ft_strchr(flags, 's'))
				ft_putnbr(sum / 2);
			else
				ft_putnbr(sum);
			ft_putchar('\n');
		}
	}
	sort_by_flags(&lst, flags);
	while (lst)
	{
		out(&lst, flags, size, path);
		ft_impdel(&lst, del_pars);
	}
	free (size);
}
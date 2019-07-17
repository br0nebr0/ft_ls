#include "ft_ls.h"

int ch_nbr_sz(int size, int nbr)
{
	char *str;

	str = ft_itoa(nbr);
	if ((int) ft_strlen(str) > size)
		size = ft_strlen(str);
	ft_strdel(&str);
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
	int *size;
	t_file *stat;

	size = (int *) ft_memalloc(sizeof(int) * 5);
	while (list)
	{
		stat = (t_file *) list->content;
		if( ft_strchr(flags, 'k'))
			size[0] = ch_nbr_sz(size[0], stat->blk);
		if(ft_strchr(flags, 's'))
			size[0] = ch_nbr_sz(size[0], stat->blk / 2);
		size[1] = ch_nbr_sz(size[1], stat->lnk);
		if(ft_strchr(flags, 'n'))
			size[2] = ch_nbr_sz(size[2], getpwuid(stat->usr)->pw_uid);
		if(!ft_strchr(flags, 'n'))
			size[2] = ch_str_sz(size[2], getpwuid(stat->usr)->pw_name);
		if(ft_strchr(flags, 'n'))
			size[3] = ch_nbr_sz(size[3], getgrgid(stat->usr)->gr_gid);
		if(!ft_strchr(flags, 'n'))
			size[3] = ch_str_sz(size[3], getgrgid(stat->usr)->gr_name);
		size[4] = ch_nbr_sz(size[4], stat->size);			
		list = list->next;
	}
	return (size);
}

void out(t_imp **params, char *flags, int *size)
{
	t_imp *lst;
	t_file *buf;

	lst = *params;
	buf = (t_file *) (lst->content);
		if(ft_strchr(flags, 'a'))
			printdirs(buf, flags, size);
		else 
		{
			if (ft_strchr(flags, 'A') && (!ft_strequ(buf->name, "..") && !ft_strequ(buf->name, ".")))
			printdirs(buf, flags, size);
			else if (((buf->name)[0] == '.' || (buf->name)[0] != '~') && ft_strchr(flags, 'd'))
				printdirs(buf, flags, size);
			else if ((buf->name)[0] != '.' && (buf->name)[0] != '~')
				printdirs(buf, flags, size);
		}
}

void output(t_imp **params, char *flags, int sum)
{
	t_imp *lst;
	int		*size;

	lst = *params;
	size = NULL;
	if (find(flags, "longOks"))
	{
	size = get_sizes(lst, flags);
	ft_putstr("total: ");
		if (ft_strchr(flags, 's'))
			ft_putnbr(sum / 2);
		else
			ft_putnbr(sum);
	ft_putchar('\n');
	}
	sort_by_flags(&lst, flags);
	while (lst)
	{
		out(&lst, flags, size);
		ft_impdel(&lst, del_pars);
	}
	if (size)
		free(size);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_folder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:30:20 by waeron-g          #+#    #+#             */
/*   Updated: 2019/06/10 17:24:01 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*добавляем слэши в случае их отсутствия*/
char *changepath(char *path)
{
	char *str;

	if ((ft_strchr(path, '/') + 1) != 0 && !ft_strequ(path, "."))
	{
		ft_putstr(path);
		ft_putendl(":");
	}
	if ((path[ft_strlen(path)-1]) != '/')
	{
		str = ft_strjoin(path, "/");
		ft_strdel(&path);
		return(str);
	}
	return (path);
}

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

t_imp *rev_list(t_imp *list)
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
		*list = rev_list(*list);

}

int *get_sizes(t_imp *list, char *flags)
{
	int *size;
	t_file *stat;
	char *buf;

	size = (int *)malloc(sizeof(int) * 5);
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
	size[3] = 0;
	size[4] = 0;
	while (list)
	{
		stat = (t_file *) list->content;
		buf = ft_itoa(stat->blk);
		if( ft_strchr(flags, 'k') && (int) ft_strlen(buf) > size[0])
			size[0] = ft_strlen(buf);
		ft_strdel(&buf);
		buf = ft_itoa(stat->blk / 2);
		if(ft_strchr(flags, 's') && (int) ft_strlen(buf) > size[0])
			size[0] = ft_strlen(buf);
		ft_strdel(&buf);
		buf = ft_itoa(stat->lnk);
		if((int) ft_strlen(buf) > size[1])
			size[1] = ft_strlen(buf);
		ft_strdel(&buf);
		buf = ft_itoa(getpwuid(stat->usr)->pw_uid);
		if(ft_strchr(flags, 'n') && (int) ft_strlen(buf) > size[2])
			size[2] = ft_strlen(buf);
		ft_strdel(&buf);
		if(!ft_strchr(flags, 'n') && (int) ft_strlen(getpwuid(stat->usr)->pw_name) > size[2])
			size[2] = ft_strlen(getpwuid(stat->usr)->pw_name);
		if(ft_strchr(flags, 'n') && (int) ft_strlen(ft_itoa(getgrgid(stat->usr)->gr_gid)) > size[3])
			size[3] = ft_strlen(ft_itoa(getgrgid(stat->usr)->gr_gid));
		if(!ft_strchr(flags, 'n') && (int) ft_strlen(getgrgid(stat->usr)->gr_name) > size[3])
			size[3] = ft_strlen(getgrgid(stat->usr)->gr_name);
		if(!ft_strchr(flags, 'n') && (int) ft_strlen(getgrgid(stat->usr)->gr_name) > size[3])
			size[3] = ft_strlen(getgrgid(stat->usr)->gr_name);
		buf = ft_itoa(stat->size);
		if((int) ft_strlen(buf) > size[4])
			size[4] = ft_strlen(buf);
		ft_strdel(&buf);			
		list = list->next;
	}
	return (size);
}

void output(t_imp **params, char *flags, int sum)
{
	t_imp *lst;
	int		*size;
	t_file	*buf;

	lst = *params;
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
		buf = (t_file *) (lst->content);
		if(ft_strchr(flags, 'a'))
			printdirs(buf, flags, size);
		else 
		{
			if (ft_strchr(flags, 'A') && (!ft_strequ(buf->name, "..") && !ft_strequ(buf->name, ".")))
			printdirs(buf, flags, size);
		else if ((buf->name)[0]!= '.')
			printdirs(buf, flags, size);
		}
		ft_impdel(&lst, del_pars);
	}
	if (find(flags, "longOks"))
		free(size);
}
/* Проверка основных флагов и пути */
int read_folders(char **path, char *flags)
{
	t_ls *rd;
	int sum;
	t_imp *folds;
	t_imp *params;
	char	*buf;

	sum = 0;
	folds = NULL;
	params = NULL;
	rd = (t_ls *) malloc(sizeof(t_ls));
	if(!(rd->fld = opendir(*path)))
	{
		free (rd);
	 	return (-1);
	}
	*path = changepath(*path);
	while((rd->entry = readdir(rd->fld)) != NULL)
	{
		buf = ft_strjoin(*path,rd->entry->d_name);
		lstat(buf, &(rd->buf));
		ft_strdel(&buf);
		get_dirs(&folds, rd, *path, flags);
		get_params(&params, rd);
		sum = calcblock(sum, flags, rd->entry->d_name, rd->buf.st_blocks);
	}
	closedir(rd->fld);
	free (rd);
	output(&params, flags, sum);
	folds = (!ft_strchr(flags, 'f')) ? ft_impsort(folds, ft_impsz(folds), s_nm): folds;
	if (ft_strchr(flags, 'R'))
	recursion(&folds, flags);
	ft_strdel(&(*path));
	return (0);
}

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
		ft_putendl(path);
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

void output(t_imp **params, char *flags, int sum)
{
	t_imp *lst;

	lst = *params;
	if (find(flags, "l"))
	{
	ft_putstr("total: ");
	ft_putnbr(sum);
	ft_putchar('\n');
	}
	if (!ft_strchr(flags, 'f'))
		lst = ft_impsort(lst, ft_impsz(lst), s_name);
	if (ft_strchr(flags, 'c'))
		lst = ft_impsort(lst, ft_impsz(lst), s_ls);
	if (ft_strchr(flags, 't'))
		lst = ft_impsort(lst, ft_impsz(lst), s_lm);
	if (ft_strchr(flags, 'w'))
		lst = ft_impsort(lst, ft_impsz(lst), s_la);
	while (lst)
	{
		printdirs((t_file *) (lst->content), flags);
		ft_impdel(&lst, del_pars);
	}
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
	rd = (t_ls *) malloc(sizeof(t_ls)); /*ERROR*/
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
	recursion(&folds, flags); /*ERROR*/
	ft_strdel(&(*path));
	return (0);
}

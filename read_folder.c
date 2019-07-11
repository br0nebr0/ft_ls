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

/*HARD FUNC TO SPLIT*/
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
	if((rd->fld = opendir(*path)))
	{
		*path = changepath(*path);
		while((rd->entry = readdir(rd->fld)) != NULL)
		{
			buf = ft_strjoin(*path,rd->entry->d_name);
			stat(buf, &(rd->stat));
			ft_strdel(&buf);
			get_dirs(&folds, rd, *path, flags); //for -R
			get_params(&params, rd);
			sum = calcblock(sum, flags, rd->entry->d_name, rd->stat.st_blocks);
		}
		closedir(rd->fld);
	}
	else
	{
		stat(*path, &(rd->stat));
		rd->path = ft_strdup(ft_strrchr(*path, '/') ? ft_strrchr(*path,'/')+1 : *path);
		sum = calcblock(sum, flags, rd->path, rd->stat.st_blocks);
		get_params(&params, rd);
	}
	free (rd);
	output(&params, flags, sum);
	folds = (!ft_strchr(flags, 'f')) ? ft_impsort(folds, ft_impsz(folds), s_nm): folds;
	recursion(&folds, flags);
	ft_strdel(&(*path));
	return (0);
}

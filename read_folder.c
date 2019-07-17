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

int read_d(t_ls **rd, char *path, t_imp **files, char *flags)
{
	int sum;

	sum = 0;
	(*rd)->entry = NULL;
	(*rd)->path = ft_strdup(path);
	stat(path, &((*rd)->stat));
	sum = calcblock(sum, flags, (*rd)->path, (*rd)->stat.st_blocks);
	get_params(&(*files), *rd);
	return (sum);
}

int read_f(t_ls **rd, char *path, t_imp **files, char *flags)
{
	int sum;

	sum = 0;
	(*rd)->entry = NULL;
	stat(path, &((*rd)->stat));
	(*rd)->path = ft_strdup(ft_strrchr(path, '/') ? ft_strrchr(path,'/')+1 : path);
	sum = calcblock(sum, flags, (*rd)->path, (*rd)->stat.st_blocks);
	get_params(&(*files), *rd);
	return (sum);
}

int read_dir(t_ls **rd, char **path, t_imp **files, char *flags, t_imp **folds)
{
	int sum;
	char *buf;

	sum = 0;
	*path = changepath(*path);
		(*rd)->path = NULL;
		while(((*rd)->entry = readdir((*rd)->fld)) != NULL)
		{
			buf = ft_strjoin(*path, (*rd)->entry->d_name);
			stat(buf, &((*rd)->stat));
			ft_strdel(&buf);
			get_dirs(&(*folds), *rd, *path, flags); //for -R
			get_params(&(*files), *rd);
			sum = calcblock(sum, flags, (*rd)->entry->d_name, (*rd)->stat.st_blocks);
		}
		closedir((*rd)->fld);
	return (sum);
}

int read_folders(char **path, char *flags)
{
	t_ls *rd;
	int sum;
	t_imp *folds;
	t_imp *files;

	sum = 0;
	folds = NULL;
	files = NULL;
	rd = (t_ls *) malloc(sizeof(t_ls));
	if (ft_strchr(flags, 'd'))
		sum = read_d(&rd, *path, &files, flags);
	else if((rd->fld = opendir(*path)))
		sum = read_dir(&rd, &(*path), &files, flags, &folds);
	else
		sum = read_f(&rd, *path, &files, flags);
	free(rd->path);
	free (rd);
	folds = (!ft_strchr(flags, 'f')) ? ft_impsort(folds, ft_impsz(folds), s_nm): folds;
	output(&files, flags, sum);
	recursion(&folds, flags);
	return (0);
}

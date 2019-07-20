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

int read_dir(char **path, t_imp **files, char *flags, t_imp **folds)
{
	int sum;
	char *buf;
	t_ls *rd;

	sum = 0;
	rd = (t_ls *) malloc(sizeof(t_ls));
	*path = changepath(*path);
	rd->path = NULL;
	rd->fld = opendir(*path);
	while((rd->entry = readdir(rd->fld)) != NULL)
	{
		buf = ft_strjoin(*path, rd->entry->d_name);
		lstat(buf, &(rd->stat));
		ft_strdel(&buf);
		get_dirs(&(*folds), rd, *path, flags); //for -R
		get_params(&(*files), rd);
		sum = calcblock(sum, flags, rd->entry->d_name, rd->stat.st_blocks);
	}
	closedir(rd->fld);
	free(rd->path);
	free (rd);
	*folds = (!ft_strchr(flags, 'f')) ? ft_impsort(*folds, ft_impsz(*folds), s_nm): *folds;
	output(&(*files), flags, sum, *path);
	recursion(&(*folds), flags);
	return (sum);
}

int read_d(char *path, t_imp **files, char *flags)
{
	int sum;
	t_ls *rd;

	rd = (t_ls *) malloc(sizeof(t_ls));
	sum = 0;
	rd->entry = NULL;
	rd->path = ft_strdup(path);
	lstat(path, &(rd->stat));
	sum = calcblock(sum, flags, rd->path, rd->stat.st_blocks);
	get_params(&(*files), rd);
	free(rd->path);
	free (rd);
	output(&(*files), flags, sum, path);
	return (sum);
}

int read_f(char *path, t_imp **files, char *flags)
{
	int sum;
	char *buf;
	t_ls *rd;

	sum = 0;
	buf = ft_strnew(255);
	if(readlink(path, buf, 255) && buf[0] > 0)
		read_folders(&buf, flags);
	else
	{
		rd = (t_ls *) malloc(sizeof(t_ls));
		rd->entry = NULL;
		if(lstat(path, &(rd->stat)) > 0)
		{
			rd->path = ft_strdup(ft_strrchr(path, '/') ? ft_strrchr(path,'/')+1 : path);
			sum = calcblock(sum, flags, rd->path, rd->stat.st_blocks);
			get_params(&(*files), rd);
			ft_strdel(&buf);
			output(&(*files), flags, sum, path);
		}
		else 
		{
			get_error(path);
		}
		free (rd);
		
	}
	return (sum);
}

int read_folders(char **path, char *flags)
{
	int sum;
	t_imp *folds;
	t_imp *files;
	DIR 	*fld;

	sum = 0;
	folds = NULL;
	files = NULL;
	fld = NULL;
	if (ft_strchr(flags, 'd'))
		sum = read_d(*path, &files, flags);
	else if((fld = (opendir(*path))))
	{
		sum = read_dir(&(*path), &files, flags, &folds);
		closedir(fld);
	}
	else
		sum = read_f(*path, &files, flags);
	return (sum);
}

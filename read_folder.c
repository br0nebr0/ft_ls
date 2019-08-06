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
		return(str);
	}
	str = ft_strdup(path);
	return (str);
}
char getext(char *path, char *name)
{
	int value;

	value = getxattr(path, name);
	ft_putnbr(value);
	return (0);
}

int do_read_loop(t_imp **folds, t_imp **files, t_ls **rd, char *flags)
{
	int sum;
	char *buf;

	sum = 0;
	while(((*rd)->entry = readdir((*rd)->fld)) != NULL)
	{
		buf = ft_strjoin((*rd)->path, (*rd)->entry->d_name);
		lstat(buf, &((*rd)->stat));
		(*rd)->xattr = getext((*rd)->path, (*rd)->entry->d_name);
		ft_strdel((&buf));
		get_dirs(&(*folds), *rd, (*rd)->path, flags);
		get_params(&(*files), *rd);
		sum = calcblock(sum, flags, (*rd)->entry->d_name, (*rd)->stat.st_blocks);
	}
	return (sum);
}

int read_dir(char *path, char *flags)
{
	t_imp	*folds;
	t_imp	*files;
	t_ls	*rd;
	int		sum;

	if (ft_strchr(flags, 'd'))
		return (0);
	folds = NULL;
	files = NULL;
	rd = (t_ls *) malloc(sizeof(t_ls));
	rd->path = changepath(path);
	rd->fld = opendir(rd->path);
	sum = do_read_loop(&folds,&files, &rd, flags);
	closedir(rd->fld);
	ft_strdel(&(rd->path));
	free(rd);
	folds = (!ft_strchr(flags, 'f')) ? ft_impsort(folds, ft_impsz(folds), s_nm): folds;
	output(&files, flags, sum, path);
	recursion(&folds, flags);
	return (1);
}

int read_file(char *path, char *flags)
{
	t_ls *rd;
	t_imp	*file;

	file = NULL;
	rd = (t_ls *) malloc(sizeof(t_ls));
	rd->entry = NULL;
	rd->path = ft_strdup(path);
	lstat(path, &(rd->stat));
	get_params(&file, rd);
	output(&file, flags, -1, path);
	ft_strdel(&(rd->path));
	free(rd);
	return (0);
}

int linkaccess(char *path, char *flags)
{
	struct stat st;
	int c;
	int n;

	n = ft_strlen(path);
	stat(path, &st);
	c = path[n - 1];
	if (!S_ISDIR(st.st_mode))
	{
		if (c != 47)
			return (0);
		return (1);
	}
	if (c == 47)
		return (1);
	if (!find(flags, "longks"))
		return (1);
	return (0);
}

int read_link(char *path, char *flags)
{
	struct stat st;
	char	*buf;

	if (ft_strchr(flags, 'd'))
		return (0);
	lstat(path, &st);
	if (!S_ISLNK(st.st_mode))
		return (0);
	buf = ft_strnew(255);
	readlink(path, buf, 255);
	if (linkaccess(path, flags))
	{
		if (S_ISDIR(st.st_mode))
			read_dir(buf, flags);
		else
			read_file(buf, flags);
	}
	else
		read_file(path, flags);
	return (1);
}

int read_folders(char *path, char *flags)
{
	char *input;
	DIR  *fld;

	errno = 0;
	input = ft_strdup(path);
	if((fld = opendir(path)))
		closedir(fld);
	if (errno == 0)
	{
		if(read_dir(input, flags) == 0)
			read_file(input, flags);
	}
	else
	{
		if(errno == ENOENT || errno == EACCES ||
			(errno == ENOTDIR && path[ft_strlen(input) - 1] == '/'))
			access_dir_error(input);
		else if(errno == ENOTDIR)
			if (read_link(input,flags) == 0)
				if(read_dir(input, flags) == 0)
					read_file(input, flags);
	}
	ft_strdel(&input);
	return (0);
}
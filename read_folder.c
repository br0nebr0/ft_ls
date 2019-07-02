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

/* как обрабатывать время???*/
/* функция для добавления структуры в данные списка*/
void *get_pars(void *rd)
{
	t_file *content;
	t_ls *buf;

	buf = (t_ls *) rd;
	content = malloc(sizeof(t_file));
	content->mode = get_mode(buf->buf);
	content->lnk = buf->buf.st_nlink;
	content->usr = buf->buf.st_uid;
	content->grp = buf->buf.st_gid;
	content->la = buf->buf.st_mtim; //3 variants of time?
	content->size = buf->buf.st_size;
	content->blk = buf->buf.st_blocks;
	content->name = ft_strdup(buf->entry->d_name);
	return ((void *)content);
}

/* функция для удаления данных из списка*/
void del_pars(void **rd)
{
	t_file *buf;

	if(rd)
	{
		if (*rd)
		{
			buf = *rd;
			ft_strdel(&(buf)->mode);
			ft_strdel(&(buf)->name);
			ft_memdel((void **)&buf);
		}
	}
}

/* Собираем все данные о файле из папки*/
void get_params(t_imp **list, t_ls *rd)
{
	if(!*list)
		*list = ft_impnew(rd, get_pars);
	else
		ft_impadd(&(*list), ft_impnew(rd, get_pars));
}

int name_compr(void *lst1, void *lst2)
{
	t_file *el1;
	t_file *el2;

	el1 = (t_file *) lst1;
	el2 = (t_file *) lst2;

	if (ft_strcmp(el1->name, el2->name) > 0)
		return (1);
	return (0);
}
/*добавляем слэши в случае их отсутствия*/
char *changepath(char *path)
{
	if ((ft_strchr(path, '/') + 1) != 0 && !ft_strequ(path, "."))
		ft_putendl(path);
	return(((ft_strlen(path)-1) != '/')? ft_strjoin(path, "/") : path);
}

/* Проверка основных флагов и пути */
int read_folders(char *path, char *flags)
{
	t_ls *rd;
	int sum;
	t_imp *folds;
	t_imp *params;

	sum = 0;
	folds = NULL;
	params = NULL;
	rd = malloc(sizeof(t_ls));
	if(!(rd->fld = opendir(path)))
	 	return (-1);
	path = changepath(path);
	while((rd->entry = readdir(rd->fld)) != NULL)
	{
		/* получение параметров файла*/
		lstat(ft_strjoin(path,rd->entry->d_name), &(rd->buf));
		/* Сбор списка директорий*/
		get_dirs(&folds, rd, path, flags);
		/* Добавление данных о файле*/
		get_params(&params, rd);
		sum = calcblock(sum, flags, rd->entry->d_name, rd->buf.st_blocks);
	}
	/* Тут должна быть сортировка*/
	/* вывод и удаление списка */
	ft_putstr("total: ");
	ft_putendl(ft_itoa(sum));
	while (params)
	{
		params = ft_impsort(params, ft_impsize(params), name_compr);
		printdirs((t_file *) (params->content), flags);
		ft_impdel(&params, del_pars);
	}
	if (ft_strchr(flags, 'R'))
	recursion(&folds, flags);
	closedir(rd->fld);
	return (0);
}

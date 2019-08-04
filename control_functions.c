#include "ft_ls.h"

/*Добавление директории в список*/
void *addir(void *str)
{
	t_path *lst;

	lst = (t_path *)malloc(sizeof(t_path));
	lst->path = ft_strdup((char *) str);
	lstat(lst->path, &(lst->stat));
	return (lst);
}
/* Удаление директории из списка*/
void deldir(void **cont)
{
	t_path *buf;

	buf = (t_path *) *cont;
	ft_strdel(&(buf->path));
	ft_memdel((void **)&(*cont));
}
/* функция для добавления структуры в данные списка*/
void *set_params(void *rd)
{
	t_file *content;
	t_ls *buf;

	buf = (t_ls *) rd;
	content = malloc(sizeof(t_file));
	content->mode = get_mode(buf->stat);
	content->lnk = buf->stat.st_nlink;
	content->usr = buf->stat.st_uid;
	content->grp = buf->stat.st_gid;
	content->la = buf->stat.st_atim;
	content->lm = buf->stat.st_mtim;
	content->ls = buf->stat.st_ctim;
	content->size = buf->stat.st_size;
	content->blk = buf->stat.st_blocks;
	content->path = ft_strdup(buf->path);
	if (buf->entry)
		content->name = ft_strdup(buf->entry->d_name);
	else 
		content->name = ft_strdup(buf->path);
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
			ft_strdel(&(buf)->path);
			ft_memdel((void **)&buf);
		}
	}
}
/* Собираем все данные о файле из папки*/
void get_params(t_imp **list, t_ls *rd)
{

	if(!*list)
		*list = ft_impnew(rd, set_params);
	else
		ft_impadd(&(*list), ft_impnew(rd, set_params));
}

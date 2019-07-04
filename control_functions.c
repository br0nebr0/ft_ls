#include "ft_ls.h"

/*Добавление директории в список*/
void *addcont(void *str)
{
	char *c;

	c = (char *) ft_strdup(str);
	return (c);
}
/* Удаление директории из списка*/
void delcont(void **cont)
{
	ft_memdel(&(*cont));
}
/* функция для добавления структуры в данные списка*/
void *set_params(void *rd)
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
		*list = ft_impnew(rd, set_params);
	else
		ft_impadd(&(*list), ft_impnew(rd, set_params));
}

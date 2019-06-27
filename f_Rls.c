/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_Rls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:21:04 by waeron-g          #+#    #+#             */
/*   Updated: 2019/06/10 17:21:48 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Добавление директории в список*/
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

/* получение поддиректорий*/
void get_dirs(t_imp **folds, t_ls *rd, char *path, char *flags)
{
	char *str;

	if (ft_strchr(flags, 'R'))
	{
		str = ft_strnew(0);
		if (S_ISDIR(rd->buf.st_mode) && (ft_strequ(rd->entry->d_name, ".") == 0 &&
		(ft_strequ(rd->entry->d_name, "..") == 0)))
		{
			str = ft_strjoin(path, rd->entry->d_name);
			 if (!*folds)
				*folds = ft_impnew(str, addcont);
			 else
				ft_impadd(&(*folds), ft_impnew(str, addcont));
			ft_strdel(&str);
		}
	}
}
/* Перед следующей функцией сортировка*/
/* Обход поддиректорий и удаление пройденых */
void recursion(t_imp **folds, char *flags)
{
	if (ft_strchr(flags, 'R'))
		while(*folds)
		{
			ft_putendl("");
			if((char*)(*folds)->content)
				read_folders((char *)(*folds)->content, flags);
			ft_impdel(&(*folds), delcont);
		}
}

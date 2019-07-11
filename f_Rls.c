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

/* получение поддиректорий*/
void get_dirs(t_imp **folds, t_ls *rd, char *path, char *flags)
{
	char *str;

	if (ft_strchr(flags, 'R'))
	{
		if (S_ISDIR(rd->stat.st_mode) && (ft_strequ(rd->entry->d_name, ".") == 0 &&
		(ft_strequ(rd->entry->d_name, "..") == 0)))
		{
			str = ft_strjoin(path, rd->entry->d_name);
			 if (!*folds)
				*folds = ft_impnew(str, addir);
			 else
				ft_impadd(&(*folds), ft_impnew(str, addir));
			ft_strdel(&str);
		}
	}
}
void recursion(t_imp **folds, char *flags)
{
	if (ft_strchr(flags, 'R'))
		while(*folds)
		{
			ft_putendl("");
			if(((t_path *)(*folds)->content)->path)
				read_folders(&((t_path *)(*folds)->content)->path, flags);
			ft_impdel(&(*folds), deldir);
		}
}

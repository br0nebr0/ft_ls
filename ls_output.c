/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:22:43 by waeron-g          #+#    #+#             */
/*   Updated: 2019/06/10 17:23:39 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Читаем права файла */
char *get_mode(struct stat file)
{
	char *mode;

	mode = ft_strnew(10);
	mode[0] = (S_ISDIR(file.st_mode)) ? 'd' : '-';
	mode[0] = (S_ISREG(file.st_mode)) ? '-' : mode[0];
	mode[0] = (S_ISBLK(file.st_mode)) ? 'b' : mode[0];
	mode[0] = (S_ISCHR(file.st_mode)) ? 'c' : mode[0];
	mode[0] = (S_ISFIFO(file.st_mode)) ? 'p' : mode[0];
	mode[0] = (S_ISLNK(file.st_mode)) ? 'l' : mode[0];
	mode[0] = (S_ISSOCK(file.st_mode)) ? 's' : mode[0];
	mode[1] = (file.st_mode & S_IRUSR) ? 'r' : '-';
	mode[2] = (file.st_mode & S_IWUSR) ? 'w' : '-';
	mode[3] = (file.st_mode & S_IXUSR) ? 'x' : '-';
	mode[4] = (file.st_mode & S_IRGRP) ? 'r' : '-';
	mode[5] = (file.st_mode & S_IWGRP) ? 'w' : '-';
	mode[6] = (file.st_mode & S_IXGRP) ? 'x' : '-';
	mode[7] = (file.st_mode & S_IROTH) ? 'r' : '-';
	mode[8] = (file.st_mode & S_IWOTH) ? 'w' : '-';
	mode[9] = (file.st_mode & S_IXOTH) ? 'x' : '-';
	return (mode);
}

/* выводим все что прочли*/
void printdirs(t_file *buf, char *flags)
{
	char *temp;

	temp = ft_strdup(ctime(&(buf->la.tv_sec)));
	temp[ft_strlen(temp) - 1] = 0;
	if (ft_strchr(flags, 'l'))
	{
		ft_putnbr(buf->blk);
		ft_putchar(' ');
		ft_putstr(buf->mode);
		ft_putchar(' ');
		ft_putnbr(buf->lnk);
		ft_putchar(' ');
		ft_putstr(getpwuid(buf->usr)->pw_name);
		ft_putchar(' ');
		ft_putstr(getgrgid(buf->usr)->gr_name);
		ft_putchar(' ');
		ft_putstr(temp);
		ft_strdel(&temp);
		ft_putchar(' ');
		ft_putnbr(buf->size);
		ft_putchar(' ');
	}
	ft_putendl(buf->name);
	
}

/* Вычисление суммы блоков в зависимости от флагов */
int calcblock(int sum, char *flags, char *name, int size)
{
	if (!ft_strchr(flags, 'a') && ft_strequ(name, ".."))
		sum -= size;
	else if ((!ft_strchr(flags, 'A') && !ft_strchr(flags, 'a'))
	&& name[0] == '.')
			sum -= size;
		sum += size;
	return (sum);
}
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
	mode[3] = (file.st_mode & S_ISUID) ? 's' : mode[3];
	mode[4] = (file.st_mode & S_IRGRP) ? 'r' : '-';
	mode[5] = (file.st_mode & S_IWGRP) ? 'w' : '-';
	mode[6] = (file.st_mode & S_IXGRP) ? 'x' : '-';
	mode[6] = (file.st_mode & S_ISGID) ? 's' : mode[6];
	mode[7] = (file.st_mode & S_IROTH) ? 'r' : '-';
	mode[8] = (file.st_mode & S_IWOTH) ? 'w' : '-';
	mode[9] = (file.st_mode & S_IXOTH) ? 'x' : '-';
	return (mode);
}

void symbols(char *mode)
{
	if (mode[0] == 'd')
		ft_putchar('/');
	else if (mode[0] == 'l')
		ft_putchar('@');
	else if (mode[0] == 's')
		ft_putchar('=');
	else if (mode[0] == 'p')
		ft_putchar('|');
	else if (ft_strchr(mode, 'x'))
		ft_putchar('*');

}

void printgroups(t_file *buf, char *flags, int *size)
{
	char *bff;

	bff = (ft_strchr(flags, 'n')) ? ft_itoa(getpwuid(buf->usr)->pw_uid) :
		ft_strdup(getpwuid(buf->usr)->pw_name);
		printwspaces(size[2] - ft_strlen(bff));
		printword(bff);
		ft_strdel(&bff);
	if(!ft_strchr(flags, 'o'))
	{
		bff = (ft_strchr(flags, 'n')) ? ft_itoa(getgrgid(buf->usr)->gr_gid) :
		ft_strdup(getgrgid(buf->usr)->gr_name);
		printwspaces(size[2] - ft_strlen(bff));
		printword(bff);
		ft_strdel(&bff);
	}
}

void printlong(t_file *buf, char *flags, int *size, char *time)
{
	char *bff;

	if (ft_strchr(flags, 'k'))
	{
		bff = ft_itoa(buf->blk);
		printwspaces(size[0] - (int) ft_strlen(bff));
		printnum(buf->blk);
		ft_strdel(&bff);
	}
	printword(buf->mode);
	bff = ft_itoa(buf->lnk);
	printwspaces(size[1] - ft_strlen(bff));
	printnum(buf->lnk);
	ft_strdel(&bff);
	printgroups(buf, flags, size);
	printword(time);
	bff = ft_itoa(buf->size);
	printwspaces(size[4] - ft_strlen(bff));
	ft_strdel(&bff);
	printnum(buf->size);
}
/* выводим все что прочли*/
void color_out(char *mode)
{
	if(mode[0] == 'd')
	{
		if (mode[7] == 'w')
		{
			if(mode[9] == 't')
				ft_putstr(f_wrst);
			else
				ft_putstr(f_wrnst);
		}
		else
			ft_putstr(f_dir);
	}
	else
	{
		if(mode[0] == 'b')
			ft_putstr(f_blsp);
		else if(mode[0] == 'c')
			ft_putstr(f_chsp);
		else if(mode[0] == 's')
			ft_putstr(f_sock);
		else if(mode[0] == 'p')
			ft_putstr(f_pipe);
		else if(mode[0] == 'l')
			ft_putstr(f_slink);
		else if(ft_strchr(mode, 'x') || ft_strchr(mode, 's'))
		{
			if (mode[3] == 's')
				ft_putstr(f_exuid);			
			else if (mode[6] == 's')
				ft_putstr(f_exgid);
			else
				ft_putstr(f_exec);
		}
	}
}

void printlink(char *flags, char *path, char *file, struct stat st)
{
	char *buf;
	char *fp;
	struct stat	rd;
	char *mode;

	buf = ft_strnew(255);
	fp = ft_strjoin(path, file);
	stat(fp, &(rd));
	if (S_ISLNK(st.st_mode) && ft_strchr(flags, 'l'))
	{
		readlink(fp, buf, 255);
		ft_putstr(f_clear);
		ft_putstr((buf[0] > 0) ? " -> " : "");
		if (ft_strchr(flags, 'G'))
		{
			mode = get_mode(rd);
			color_out(mode);		
		}
		ft_putstr(buf);
	}
	ft_strdel(&buf);
	ft_strdel(&fp);
}

void printdirs(t_file *file, char *flags, int *size, char *path)
{
	char *time;
	char *buf;
	struct stat st;

	buf = ft_strjoin(path, file->name);
	time = get_time(file, flags);
	if (ft_strchr(flags, 'l'))
		printlong(file, flags, size, time);	
	ft_strdel(&time);
	if (ft_strchr(flags, 'G'))
		color_out(file->mode);
	ft_putstr(file->name);
	lstat(buf, &(st));
	printlink(flags, path, file->name, st);
	if(ft_strchr(flags, 'p') && file->mode[0] == 'd')
		ft_putchar('/');
	if(ft_strchr(flags, 'F'))
		symbols(file->mode);
	ft_putendl(f_clear);
	ft_strdel(&buf);
}

/* Вычисление суммы блоков в зависимости от флагов */
int calcblock(int sum, char *flags, char *name, int size)
{
	if ((!ft_strchr(flags, 'a') && ft_strequ(name, "..")))
		sum -= size;
	else if ((!ft_strchr(flags, 'A') && !ft_strchr(flags, 'a'))
	&& name[0] == '.' && !ft_strchr(flags, 'd'))
			sum -= size;
		sum += size;
	return (sum);
}
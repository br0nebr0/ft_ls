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


char get_file_type(struct stat file)
{
	if (S_ISDIR(file.st_mode))
		return ('d');
	if (S_ISREG(file.st_mode))
		return ('-');
	if (S_ISBLK(file.st_mode))
		return ('b');
	if (S_ISCHR(file.st_mode))
		return ('c');
	if (S_ISFIFO(file.st_mode))
		return ('p');
	if (S_ISLNK(file.st_mode))
		return ('l');
	if (S_ISSOCK(file.st_mode))
		return ('s');
	return ('?');
}
/* Читаем права файла */
char *get_mode(struct stat file)
{
	char *mode;

	mode = ft_strnew(10);
	mode[0] = get_file_type(file);
	mode[1] = (file.st_mode & S_IRUSR) ? 'r' : '-';
	mode[2] = (file.st_mode & S_IWUSR) ? 'w' : '-';
	mode[3] = (file.st_mode & S_IXUSR) ? 'x' : '-';
	mode[4] = (file.st_mode & S_IRGRP) ? 'r' : '-';
	mode[5] = (file.st_mode & S_IWGRP) ? 'w' : '-';
	mode[6] = (file.st_mode & S_IXGRP) ? 'x' : '-';
	mode[7] = (file.st_mode & S_IROTH) ? 'r' : '-';
	mode[8] = (file.st_mode & S_IWOTH) ? 'w' : '-';
	mode[9] = (file.st_mode & S_IXOTH) ? 'x' : '-';
	if (file.st_mode & S_ISUID)
		mode[3] = (file.st_mode & S_IXUSR) ? 's' : 'S';
	if (file.st_mode & S_ISGID)
		mode[6] = (file.st_mode & S_IXGRP) ? 's' : 'S';
	if (file.st_mode & S_ISVTX)
		mode[9] = (file.st_mode & S_IXOTH) ? 't' : 'T';
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
	struct passwd *pass;

	pass = getpwuid(buf->usr);
	if (!(pass))
	bff = (ft_strchr(flags, 'n')) ? ft_itoa(0) : ft_strdup("root");
	else if (ft_strchr (flags, 'n'))
		bff = ft_itoa(pass->pw_uid);
	else
	{
		bff = ft_strdup(pass->pw_name);
	}
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

	if (find(flags, "sk"))
	{
		bff = ft_itoa((ft_strchr(flags, 's'))? buf->blk / 2 : buf->blk);
		printwspaces(size[0] - (int) ft_strlen(bff));
		printnum((ft_strchr(flags, 's'))? buf->blk / 2 : buf->blk);
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

void printlink(char *flags, char *path, char *name)
{
	char *buf;
	struct stat	rd;
	char *mode;
	char *url;

	buf = ft_strnew(255);
	url = (ft_strequ(path, name) == 1) ? ft_strdup(path) : ft_strjoin(path, name);
	readlink(url, buf, 255);
	ft_putstr(f_clear);
	ft_putstr((buf[0] > 0) ? " -> " : "");
	if (ft_strchr(flags, 'G') && stat(buf, &rd) >= 0)
	{
		mode = get_mode(rd);
		color_out(mode);
		ft_strdel(&mode);	
	}
	ft_putstr(buf);
	ft_strdel(&buf);
	ft_strdel(&url);
}

void printdirs(t_file *file, char *flags, int *size, char *path)
{
	char *time;
	char *buf;

	buf = ft_strjoin(path, file->name);
	time = get_time(file, flags);
	if (find(flags, "longks"))
		printlong(file, flags, size, time);	
	ft_strdel(&time);
	if (ft_strchr(flags, 'G'))
		color_out(file->mode);
	ft_putstr(file->name);
	if(file->mode[0] == 'l')
		printlink(flags, file->path, file->name);
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
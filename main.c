#include "ft_ls.h"

void get_error(t_imp **lst, char **str, int code)
{
	if (code < 0)
	{
		if (lst)
			while (*lst)
				ft_impdel(&(*lst), deldir);
		ft_strdel(&(*str));
		ft_putendl("ERROR!!!");
	}
}

/*"@1AaBbCcdFfGgHhikLlmnOoPpqRrSsTtuvWwx"*/
int ft_addline(char **buf, char *arg)
{
	int i;
	int j;

	i = ft_strlen(arg);
	j = 0;
	while (j < i)
	{
		if (!ft_strchr("@1AaBbCcdFfGgHhikLlmnOoPpqRrSsTtuvWwx", arg[j]))
		{
			ft_strdel(&(*buf));
			return (0);
		}
		if (!ft_strchr(*buf, arg[j]))
			*buf = ft_strncat(*buf, arg + j, 1);
		j++;
	}
	return (1);
}

void ft_addpath(t_imp **path, char *arg)
{
	if(!*path)
		*path = ft_impnew(arg, addir);
	else
		ft_impadd(&(*path), ft_impnew(arg, addir));
}

int get_args(int gc, char **gv, t_imp **path, char **flags)
{
	int i;

	if (gc == 1)
	{
		*path = ft_impnew(".", addir);
		*flags = ft_strdup("");
		return(0);
	}
	i = 1;
	while(i < gc)
	{
		if (gv[i][0] == '-' && *path)
			return (-1);
		if (gv[i][0] == '-')
			if(!ft_addline(&(*flags), gv[i]+1))
				return (-1);
		if(gv[i][0] != '-')
			ft_addpath(&(*path), gv[i]);
		i++;
	}
	*path = (!*path) ? ft_impnew(".", addir) : *path;
	return (0);
}

char *get_path(void *lst)
{
	t_path *buf;
	char *str;

	buf = (t_path *) lst;
	str = ft_strdup(buf->path);
	buf = NULL;
	return (str);

}

int	main(int gc, char **gv) 
{
	t_imp	*path;
	int		test;
	char	*flags;
	char *buf;

	path = NULL;
	flags = ft_strnew(37);
	if((test = get_args(gc, gv, &path, &flags)) < 0)
	{
		get_error(&path, &flags, test);
		exit (0);
	}
	path = (!ft_strchr(flags, 'f')) ? ft_impsort(path, ft_impsz(path), s_pt): path;
	while(path && test >= 0)
	{
		buf = get_path(path->content);
		test = read_folders(&buf, flags);
		ft_impdel(&path, deldir);
		ft_strdel(&buf);		
	}
	if (test < 0)
	{
		get_error(&path, &flags, test);
		exit (0);
	}
	ft_strdel(&flags);
	exit(1);
}
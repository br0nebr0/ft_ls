#include "ft_ls.h"

void get_error(t_imp **lst, char **str, int code)
{
	if (code < 0)
	{
		if (lst)
			while (*lst)
				ft_impdel(&(*lst), deldir);
		ft_strdel(&(*str));
		ft_putstr("\x1b[31m\x1b[47m");
		ft_putstr("ERROR!!!");
		ft_putendl("\x1b[0m");
		exit (0);
	}
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
	int		err;
	char	*flags;
	char *buf;
	
	path = NULL;
	flags = ft_strnew(24);
	if((err = get_args(gc, gv, &path, &flags)) < 0)
		get_error(&path, &flags, err);
	path = (!ft_strchr(flags, 'f')) ? ft_impsort(path, ft_impsz(path), s_pt): path;
	while(path && err >= 0)
	{
		buf = get_path(path->content);
		err = read_folders(&buf, flags);
		ft_impdel(&path, deldir);
		ft_strdel(&buf);		
	}
	if (err < 0)
		get_error(&path, &flags, err);
	ft_strdel(&flags);
	exit(1);
}
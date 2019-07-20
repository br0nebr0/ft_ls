#include "ft_ls.h"

void get_error(char *str)
{
	char *buf;

	buf = ft_strjoin("ft_ls: ", str);
	perror(buf);
	ft_strdel(&buf);
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
	err = get_args(gc, gv, &path, &flags);
	path = (!ft_strchr(flags, 'f')) ? ft_impsort(path, ft_impsz(path), s_pt): path;
	while(path && err >= 0)
	{
		buf = get_path(path->content);
		err = read_folders(&buf, flags);
		ft_impdel(&path, deldir);
		ft_strdel(&buf);		
	}
	ft_strdel(&flags);
	exit(1);
}
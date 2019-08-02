#include "ft_ls.h"

char get_err_flag(char *flags)
{
	while (*flags)
	{
		if (!ft_strchr("@1AacdFfGgklnopRrSsTtUuw", *flags))
			break ;
		flags++;
	}
	return(*flags);
}

void usage_error(char **flags, t_imp **path)
{
	ft_impdellist(&(*path), deldir);
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(get_err_flag(*flags), 2);
	ft_putchar_fd('\n',2);
	ft_strdel(&(*flags));
	ft_putendl_fd(ERR_USAGE, 2);
	exit (2);
}

void access_dir_error (char *path)
{
	char *buf;
	char *b;


		buf = ft_strjoin("ft_ls: cannot open '", path);
		b = ft_strjoin(buf, "'");
		ft_strdel(&buf);
		perror(b);
		ft_strdel(&b);
}

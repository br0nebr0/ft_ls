#include "ft_ls.h"

char *get_flags(int gc, char **gv)
{
	char *chk;
	char *buf;
	int i;
	int j;

	i = 1;
	chk = ft_strdup("1AaBbCcDdFfGgHhikLlmNnopQqRrSstUuvwXx");
	buf = ft_strnew(0);
	while(i < gc)
	{
		if (gv[i][0] == '-')
		{
			j = 1;
			while (j < (int)ft_strlen(gv[i]))
			{
				if (!ft_strchr(chk, gv[i][j]))
				{
					ft_strdel(&buf);
					return ("e");
				}
				j++;	
			}
			buf = ft_strjoin(buf, gv[i]+1);
		}
		i++;
	}
	return (buf);
}

int g_pars(int gc, char **gv, char **path, char **flags)
{

	if (gc == 1)
	{
		*path = ft_strdup(".");
		*flags = ft_strdup("");
		return (0);
	}
	*flags = get_flags(gc, gv);
	if (ft_strchr(*flags, 'e'))
		return (-1);
	if (gv[gc - 1][0] != '-')
		*path = ft_strdup(gv[gc - 1]);
	else
		*path = ft_strdup(".");
	return (0);
}

int	main(int gc, const char **gv) 
{
	char	*path;
	int		test;
	char	*flags;

	test = g_pars(gc, (char **) gv, &path, &flags);
	if (test < 0)
	{
		ft_putendl("ERROR!!!!");
		return (0);
	}
	test = read_folders(path, flags);
	if (test == -1)
		ft_putendl("ERROR!!!!");
	ft_strdel(&path);
	ft_strdel(&flags);
	return(0);
}
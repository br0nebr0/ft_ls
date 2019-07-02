#include "ft_ls.h"

void addchar(char **line, char c)
{
	char *buf;

	if (!*line)
		buf = ft_strnew(1);
	else
		buf = ft_strnew(ft_strlen(*line)+1);
	buf = ft_strcat(buf, *line);
	buf[ft_strlen(*line)] = c;
	if (*line)
		ft_strdel(&(*line));
	*line = buf;
}

void addlines(char **line1, char *line2)
{
	int i;
	char *buf;

	i = 1;
	buf = NULL;
	if (line1)
		buf = ft_strdup(*line1);
	while (i < (int)ft_strlen(line2))
	{
		if (!ft_strchr("1AaBbCcDdFfGgHhikLlmNnopQqRrSstUuvwXx", line2[i]))
		{
			addchar(&buf, 'e');

			break;
		}
		if (!ft_strchr(buf, line2[i]))
			addchar(&buf, line2[i]);
		i++;	
	}
	ft_strdel(&(*line1));
	*line1 = buf;
}

char *get_flags(int gc, char **gv)
{
	char *buf;
	int i;

	i = 1;
	buf = NULL;
	while(i < gc)
	{
		if (gv[i][0] == '-')
			addlines(&buf, gv[i] + 1);
		ft_putendl("here1");
		i++;
	}
	return (buf);
}

int g_pars(int gc, char **gv, char **path, char **flags)
{

	*path = NULL;
	*flags = NULL;
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

int	main(int gc, char **gv) 
{
	char	*path;
	int		test;
	char	*flags;

	flags = get_flags(gc, gv);
	//test = g_pars(gc, gv, &path, &flags);
	ft_putendl(flags);
	return (0);
	if (test < 0)
	{
		ft_putendl("ERROR!!!!");
		ft_strdel(&path);
		ft_strdel(&flags);
		return (0);
	}
	//test = read_folders(&path, flags);
	ft_strdel(&flags);
	ft_strdel(&path);
	if (test == -1)
		ft_putendl("ERROR!!!!");
	return(0);
}
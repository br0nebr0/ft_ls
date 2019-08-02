#include "ft_ls.h"
/*"@1AaBbCcdFfGgHhikLlmnOoPpqRrSsTtuvWwx"*/
int ft_addline(char **buf, char *arg)
{
	int i;
	int j;

	i = ft_strlen(arg);
	j = 0;
	while (j < i)
	{
		if (!ft_strchr("@1AacdFfGgklnopRrSsTtUuw", arg[j]))
		{
			*buf = ft_strncat(*buf, arg + j, 1);
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
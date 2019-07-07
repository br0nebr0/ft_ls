#include "ft_ls.h"

void cut_time(char *tm, int mode)
{
	if (mode == 1)
		ft_strclr(tm + ft_strlen(tm) - 9);
	if (mode == 2)
	{
		ft_memmove(tm + ft_strlen(tm) - 13,  (const char *) tm + ft_strlen(tm) - 5, 4);
		tm[ft_strlen(tm) - 14] = ' ';
		ft_strclr(tm + ft_strlen(tm) - 9);
	}
}

char *get_time(t_file *buf, char *flags)
{
	char *tm;

	if (ft_strchr(flags, 'c'))
	{
		tm = ft_strdup(ctime(&(buf->ls.tv_sec)) + 4);
		if (time(NULL) - buf->ls.tv_sec > 31556926)
			cut_time(tm, 2);
		else
			cut_time(tm, 1);
		return (tm);
	}
	if (ft_strchr(flags, 'w'))
	{
		tm = ft_strdup(ctime(&(buf->la.tv_sec)) + 4);
		if (time(NULL) - buf->la.tv_sec > 31556926)
			cut_time(tm, 2);
		else
			cut_time(tm, 1);
		return (tm);
		
	}
	tm = ft_strdup(ctime(&(buf->lm.tv_sec)) + 4);
	if (time(NULL) - buf->lm.tv_sec > 31556926)
			cut_time(tm, 2);
		else
			cut_time(tm, 1);
		return (tm);
}
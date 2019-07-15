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
	struct timespec now;

	if (ft_strchr(flags, 'c'))
		now = buf->ls;
	else if (ft_strchr(flags, 'w'))
		now = buf->la;
	else
		now = buf->lm;
	if (ft_strchr(flags, 'T'))
	{
		tm = ft_strdup(ctime(&(now.tv_sec)));
		tm[ft_strlen(tm) - 1] = 0;
		return (tm);
	}
	tm = ft_strdup(ctime(&(now.tv_sec)) + 4);
	if (time(NULL) - now.tv_sec > 31556926)
		cut_time(tm, 2);
	else
		cut_time(tm, 1);
	return (tm);

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:43:04 by waeron-g          #+#    #+#             */
/*   Updated: 2019/06/10 17:20:24 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>

/* 
	I forgot this struct, but it important
*/
typedef struct s_ls
{
	DIR				*fld;
	struct dirent	*entry;
	struct stat		buf;
} 				t_ls;

/* mod: acesss&typefile; lnk:links_count;
usr:user_id; grp: group_id; tm: contain 3 dif. time val;
blk:  blocks_count; name: filename;
*/
typedef struct s_file
{
	char			*mode;
	int				lnk;
	uid_t			usr;
	gid_t			grp;
	struct timespec	la;
	int				blk;
	int				size;
	char			*name;
}				t_file;

/*List control functions*/
void *addcont(void *str);
void delcont(void **cont);
void *set_params(void *rd);
void del_pars(void **rd);
void get_params(t_imp **list, t_ls *rd);
/*Sort functions*/
int name_compr(void *lst1, void *lst2);
/*other funcs*/
int read_folders(char **path, char *flags);
char *get_mode(struct stat file);
void recursion(t_imp **folds, char *flags);
char *changepath(char *path);
void printbuf(char *buffer, int sum, char *flags);
void get_dirs(t_imp **folds, t_ls *rd, char *path, char *flags);
int calcblock(int sum, char *flags, char *name, int size);
void printdirs(t_file *buf, char *flags);
#endif

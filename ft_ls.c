/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ction <ction@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:34:38 by ction             #+#    #+#             */
/*   Updated: 2019/06/10 16:11:12 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int gc, const char **gv) 
{
	char	*path;
	int		test;
	char	*flags;

	if (gc > 1)
	{
		flags = (gv[1][0] == '-')? ft_strdup(gv[1]) : "";
	 	path = (gv[gc - 1][0] !='-') ? ft_strdup(gv[gc - 1]): ".";
	}
	else
	{
		path = ft_strdup(".");
		flags = ft_strdup("");
	}
	test = read_folders(path, flags);
	if (test == -1)
		ft_putendl("ERROR!!!!");
	return(0);
}

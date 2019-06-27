/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:33:59 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/08 17:56:36 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;
	int				flag;
	unsigned char	cc;

	flag = 0;
	i = 0;
	s = (unsigned char *)str;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (s[i] == cc)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (0);
	return (&s[i]);
}

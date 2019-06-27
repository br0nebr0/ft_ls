/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:36:22 by waeron-g          #+#    #+#             */
/*   Updated: 2018/11/30 15:57:59 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s = dst;
	while (i < len)
	{
		if (*src)
		{
			*dst = *src;
			src++;
		}
		else
			*dst = 0;
		dst++;
		i++;
	}
	dst = s;
	return (dst);
}

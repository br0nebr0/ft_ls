/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:37:35 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/10 21:51:12 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(void *src, size_t n)
{
	size_t	i;
	char	*c;

	i = 0;
	c = (char*)src;
	while (c[i] && i < n)
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	srcsize;

	srcsize = ft_strlen((char *)src);
	dstsize = ft_strnlen(dst, size);
	if (dstsize == size)
		return (dstsize + srcsize);
	if (srcsize < size - dstsize)
	{
		ft_memcpy(dst + dstsize, src, srcsize + 1);
		dst[srcsize + dstsize] = '\0';
	}
	else
	{
		ft_memcpy(dst + dstsize, src, size - dstsize - 1);
		dst[size - 1] = '\0';
	}
	return (dstsize + srcsize);
}

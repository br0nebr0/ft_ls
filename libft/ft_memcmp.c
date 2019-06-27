/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:34:28 by waeron-g          #+#    #+#             */
/*   Updated: 2018/11/30 15:36:02 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				sum;
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	sum = 0;
	i = 0;
	d = (unsigned char *)s1;
	s = (unsigned char *)s2;
	while (i < n)
	{
		sum = d[i] - s[i];
		if (sum != 0)
			break ;
		i++;
	}
	return (sum);
}

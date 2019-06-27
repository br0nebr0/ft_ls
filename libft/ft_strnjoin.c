/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:13:26 by waeron-g          #+#    #+#             */
/*   Updated: 2019/02/26 19:06:55 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(const char *str, const char *src, const int len)
{
	char	*newline;
	int		i;
	int		ln;

	if (!str || !src || len <= 0)
		return (NULL);
	ln = ((int)ft_strlen(src) < len) ? (int)ft_strlen(src) : len;
	ln += ft_strlen(str);
	newline = ft_strnew(ln);
	if (!newline)
		return (NULL);
	i = 0;
	while (i < ln && *str)
	{
		newline[i] = *str;
		str++;
		i++;
	}
	while (i < ln)
	{
		newline[i] = *src;
		i++;
		src++;
	}
	return (newline);
}

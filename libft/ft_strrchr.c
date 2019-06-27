/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:38:43 by waeron-g          #+#    #+#             */
/*   Updated: 2018/11/30 18:49:50 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;
	int		flag;

	flag = 0;
	str = (char *)s;
	i = ft_strlen(str);
	if (c == '\0')
		return (&str[i]);
	while (i > 0)
	{
		i--;
		if (str[i] == c)
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 1)
		return (&str[i]);
	return (NULL);
}

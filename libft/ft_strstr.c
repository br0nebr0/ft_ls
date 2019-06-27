/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:39:01 by waeron-g          #+#    #+#             */
/*   Updated: 2019/06/10 16:54:17 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str;
	int		n;
	int		i;

	str = (char*)haystack;
	n = ft_strlen(needle);
	if (n == 0)
		return (str);
	i = 0;
	while (*(str + i))
	{
		if (ft_strncmp(str + i, needle, n) == 0)
			return (&*(str + i));
		i++;
	}
	return (0);
}

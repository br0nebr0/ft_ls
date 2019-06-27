/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:39:33 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/10 22:32:46 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*s;

	s = haystack - 1;
	if (!*needle)
		return ((char*)haystack);
	while (*++s && len--)
		if (ft_strncmp(s, needle, ft_strlen(needle)) == 0
		&& len + 1 >= ft_strlen(needle))
			return ((char*)s);
	return (NULL);
}

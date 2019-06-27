/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:54:55 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/01 16:00:30 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char const	*str;
	int			len;

	if (!s)
		return (NULL);
	str = s;
	while ((*str == ' ' || *str == '\t' || *str == '\n') && *str)
		str++;
	len = ft_strlen(str) - 1;
	if (len < 0)
		return (ft_strsub(str, 0, 0));
	while ((str[len] == ' ' || str[len] == '\t' || str[len] == '\n'))
		len--;
	return (ft_strsub(str, 0, len + 1));
}

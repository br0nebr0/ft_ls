/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:36:19 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/01 15:58:48 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		n;
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1 && i < n)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 && i < n)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[n] = '\0';
	return (str);
}

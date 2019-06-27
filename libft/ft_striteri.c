/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:40:48 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/01 16:14:10 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int size;
	int i;

	i = 0;
	if (s && f)
	{
		size = ft_strlen(s);
		while (i < size)
		{
			f(i, &s[i]);
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlento.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:21:45 by waeron-g          #+#    #+#             */
/*   Updated: 2019/02/23 03:15:51 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlento(const char *str, const char c)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			break ;
		str++;
		i++;
	}
	return (i);
}

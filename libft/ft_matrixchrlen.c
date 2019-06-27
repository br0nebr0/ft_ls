/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixchrlen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:38:10 by waeron-g          #+#    #+#             */
/*   Updated: 2019/04/02 11:32:38 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_matrixchrlen(const char **s, int field_size, int c)
{
	int		i;
	int		j;

	j = 0;
	while (j < field_size)
	{
		i = 0;
		while (i < field_size)
		{
			if (s[j][i] == c)
				return (0);
			i++;
		}
		j++;
	}
	if (s[j] == NULL)
		return (1);
	else
		return (0);
}

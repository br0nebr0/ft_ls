/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:51:40 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/08 17:49:53 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	sum;
	int				ch;

	sum = 0;
	ch = 0;
	while (*str)
	{
		if ((*str < 9 || *str > 13) && *str != ' ')
			if (*str == '-' && ch == 0 && sum == 0)
				ch = 1;
			else if (*str == '+' && ch == 0 && sum == 0)
				ch = 2;
			else if (*str >= '0' && *str <= '9')
				sum = sum * 10 + (*str - '0');
			else
				break ;
		else if (sum > 0 || ch > 0)
			break ;
		str++;
	}
	if (sum < 0)
		return ((ch == 1) ? 0 : -1);
	return ((ch == 1) ? -sum : sum);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:05:27 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/01 16:09:20 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getnumsize(int n)
{
	int	count;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	count = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		flag;
	int		count;

	flag = (n < 0) ? 1 : 0;
	count = ft_getnumsize(n);
	if (!(str = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	str[count] = '\0';
	if (n == -2147483648)
		str = ft_strcpy(str, "-2147483648");
	else if (n == 0)
		str = ft_strcpy(str, "0");
	else
	{
		n = (n < 0) ? -n : n;
		while (n != 0)
		{
			count--;
			str[count] = (n % 10) + '0';
			n = n / 10;
		}
		str[0] = (flag == 1) ? '-' : str[0];
	}
	return (str);
}

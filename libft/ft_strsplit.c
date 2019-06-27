/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:29:41 by waeron-g          #+#    #+#             */
/*   Updated: 2018/12/03 17:20:26 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_getcount(char const *s, char c)
{
	int		flag;
	int		count;
	char	*str;
	char	**arr;

	str = (char *)s;
	count = 0;
	flag = 0;
	while (*str)
	{
		if (flag == 1 && *str == c)
			flag = 0;
		if (*str != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		str++;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr[count] = 0;
	return (arr);
}

static void	ft_frearr(char **array)
{
	while (*array)
	{
		ft_memdel((void *)&array);
	}
	ft_memdel((void *)&*array);
	array = NULL;
}

static void	ft_getwords(char **array, char const *s, char c)
{
	int		i;
	char	**buf;

	buf = array;
	while (*s)
	{
		i = 0;
		while (*s)
		{
			if (*s != c)
			{
				while (s[i] && s[i] != c)
					i++;
				if (!(*array = ft_strsub(s, 0, i)))
					ft_frearr(buf);
				break ;
			}
			s++;
		}
		s += i;
		if (!*array)
			break ;
		array++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	char	**buf;

	if (!s || !c)
		return (NULL);
	if (!(array = ft_getcount(s, c)))
		return (NULL);
	buf = array;
	ft_getwords(array, s, c);
	if (!buf)
		return (NULL);
	return (buf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:55:12 by waeron-g          #+#    #+#             */
/*   Updated: 2019/06/01 16:16:25 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_impadd(t_imp **imp, t_imp *new)
{
	t_imp *buf;

	buf = *imp;
	if (*imp == NULL)
		*imp = new;
	else
	{
		while (buf->next!=NULL)
			buf = buf->next;
		buf->next = new;
	}
}

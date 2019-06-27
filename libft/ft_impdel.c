/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:31:58 by waeron-g          #+#    #+#             */
/*   Updated: 2019/02/26 19:36:59 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_impdel(t_imp **imp, void (*del)(void **))
{
	t_imp	*buf; 

	if (imp)
	{
		buf = (*imp)->next;
		if (*imp)
		{
			del(&(*imp)->content);
			free((*imp));
			*imp = buf;
			}
		}
}

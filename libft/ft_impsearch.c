/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:57:36 by waeron-g          #+#    #+#             */
/*   Updated: 2019/02/26 22:09:39 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_imp	*ft_impsearch(t_imp *imp, int id)
{
	if (imp)
	{
		while (imp)
		{
			if (imp->id == id)
				break ;
			imp = imp->next;
		}
		return (imp);
	}
	return (NULL);
}

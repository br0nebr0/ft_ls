/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waeron-g <waeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:56:32 by waeron-g          #+#    #+#             */
/*   Updated: 2019/02/26 22:00:14 by waeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_imp	*ft_impnew(void *content, void *(*add)(void *))
{
	t_imp	*imp;

	if (!(imp = malloc(sizeof(t_imp))))
		return (NULL);
	if (!content)
		return (NULL);
	imp->content = add(content);
	imp->next = NULL;
	return (imp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 14:49:20 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:54:21 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

t_list		*ft_lstdup(t_list *beginlist)
{
	t_list	*begin_newlist;
	t_list	*tmp;
	t_list	*tmp2;

	if (!beginlist)
		return (NULL);
	if (!(begin_newlist =
				ft_lstnew(beginlist->content, beginlist->content_size)))
		return (NULL);
	tmp = begin_newlist;
	tmp2 = beginlist->next;
	while (tmp2 != NULL)
	{
		if (!(tmp->next = ft_lstnew(tmp2->content, tmp2->content_size)))
			return (NULL);
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	tmp->next = NULL;
	return (begin_newlist);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:56:48 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:55:04 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *new2;
	t_list *newlst;
	t_list *tmp;

	tmp = lst;
	if (!lst || !f)
		return (NULL);
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new = f(tmp);
	tmp = tmp->next;
	if (!(newlst = new))
		return (NULL);
	while (tmp)
	{
		if (!(new2 = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		new2 = f(tmp);
		new->next = new2;
		new = new2;
		free(new2);
		tmp = tmp->next;
	}
	return (newlst);
}

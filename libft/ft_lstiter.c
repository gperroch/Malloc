/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:01:03 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 10:54:41 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *tmp;
	t_list *tmp2;

	if (!lst || !f)
		return ;
	tmp = lst;
	tmp2 = lst->next;
	while (tmp2 != NULL)
	{
		f(tmp);
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
	f(tmp);
}

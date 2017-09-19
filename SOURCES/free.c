/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:30:24 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 12:31:07 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			free(void *ptr)
{
	t_metadata	*bloc;
	t_metadata	*area;
	short		area_free;

	if (!ptr)
		return ;
	area_free = 1;
	bloc = ptr - sizeof(t_metadata);
	if (bloc->magic_number != MAGIC_NUMBER_BLOC)
		return ;
	bloc->free = 1;
	area = bloc->prev_area;
	if (area->magic_number == MAGIC_NUMBER_AREA)
	{
		bloc = (t_metadata*)((char*)area + sizeof(t_metadata));
		while (bloc && bloc->magic_number == MAGIC_NUMBER_BLOC)
		{
			if (!bloc->free)
				area_free = 0;
			bloc = bloc->next;
		}
		if (area_free)
			ft_area_free(area);
	}
}

void		ft_area_free(t_metadata *area)
{
	if (!area->prev_area && !area->next)
		g_start = NULL;
	else if (!area->prev_area && area->next)
	{
		g_start = area->next;
		(area->next)->prev_area = NULL;
	}
	else if (area->prev_area && !area->next)
		(area->prev_area)->next = NULL;
	else if (area->prev_area && area->next)
	{
		(area->prev_area)->next = area->next;
		(area->next)->prev_area = area->prev_area;
	}
	munmap(area, area->size_total);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:30:24 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/16 14:06:11 by gperroch         ###   ########.fr       */
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
		{
			if (!area->prev_area)
				g_start = NULL;
			else
				(area->prev_area)->next = NULL;
			munmap(area, area->size_total);
		}
	}
}

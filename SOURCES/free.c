/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:30:24 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/12 14:10:39 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// ENLEVER LES 2 PRINTF DE DEBUG
// Rendre au systeme la zone memoire si elle est entierement free (munmap)

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
	{
		printf("error for object %p: pointer being freed was not allocated\n", ptr);
		return ;
	}
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
			munmap(area, area->size_total);
	}
}

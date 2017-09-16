/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:52:45 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/16 15:16:34 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			show_alloc_mem(void)
{
	void		*ptr;
	t_metadata	*bloc;
	t_metadata	*area;
	size_t		size_total;

	ptr = malloc(1);
	bloc = ptr - sizeof(t_metadata);
	free(ptr);
	area = bloc->prev_area;
	while (area->prev_area)
		area = area->prev_area;
	while (area && area->magic_number == MAGIC_NUMBER_AREA)
	{
		bloc = (t_metadata*)((char*)area + sizeof(t_metadata));
		if (area->size_data == TINY)
		{
			ft_putstr("-TINY : ");
			ft_putstr(ft_itoa((int)((char*)area + sizeof(t_metadata))));
			printf("TINY : %p\n", (char*)area + sizeof(t_metadata));
		}
		else if (area->size_data == SMALL)
			//ft_putstr("SMALL : ");
			printf("SMALL : %p\n", (char*)area + sizeof(t_metadata));
		else
			//ft_putstr("LARGE : ");
			printf("LARGE : %p\n", (char*)area + sizeof(t_metadata));
		//ft_printf("%p\n", (char*)area + sizeof(t_metadata));
		while (bloc && bloc->magic_number == MAGIC_NUMBER_BLOC)
		{
			if (!bloc->free)
				printf("%p - %p : %zu octets\n", (char*)bloc + sizeof(t_metadata), (char*)bloc + sizeof(t_metadata) + bloc->size_total, bloc->size_total);
				//ft_printf("%p - %p : %zu octets\n", (char*)bloc + sizeof(t_metadata), (char*)bloc + sizeof(t_metadata) + bloc->size_total, bloc->size_total);
			bloc = bloc->next;
		}

		area = area->next;
	}
}

void			ft_display_addr(void *ptr)
{
	
}

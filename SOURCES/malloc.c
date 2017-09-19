/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 10:00:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));
void *g_start = NULL;

void			*malloc(size_t size)
{
	t_metadata	*area;
	t_metadata	*bloc;

	area = NULL;
	bloc = NULL;
	if ((long long)size < 0)
		return (NULL);
	if (!ft_find_bloc_area(g_start, &area, size, 0))
	{
		if (!ft_new_area(g_start, &area, size))
			return (NULL);
		if (!g_start)
			g_start = area;
	}
	if (!ft_find_bloc_area(area, &bloc, size, 1))
		return (NULL);
	if (!ft_update_metadata(bloc, size))
		return (NULL);
	if (size <= SMALL && bloc->magic_number == MAGIC_NUMBER_BLOC && !bloc->next)
		ft_add_next_metadata(bloc, area);
	return ((void*)bloc + sizeof(t_metadata));
}

int				ft_find_bloc_area(t_metadata *area, t_metadata **target,
	size_t size, int bloc)
{
	t_metadata	*cursor;

	cursor = (bloc) ? (t_metadata*)((char*)area + sizeof(t_metadata)) : area;
	if (!area)
		return (0);
	while ((cursor->size_data < size || !cursor->free) && cursor->next)
		cursor = cursor->next;
	*target = cursor;
	if (cursor->size_data >= size && cursor->free)
		return (1);
	return (0);
}

int				ft_update_metadata(t_metadata *bloc, size_t size)
{
	if (bloc->magic_number != MAGIC_NUMBER_BLOC)
		return (0);
	bloc->free = 0;
	bloc->size_total = size;
	return (1);
}

int				ft_size_available(t_metadata *area, t_metadata *bloc,
	size_t size)
{
	int			current_size;
	int			size_max;

	current_size = (unsigned int)bloc + sizeof(t_metadata) + size;
	size_max = (unsigned int)area + sizeof(t_metadata) + area->size_total;
	if (current_size <= size_max)
		return (1);
	return (0);
}

int				ft_add_next_metadata(t_metadata *bloc, t_metadata *area)
{
	t_metadata	*new_bloc;
	char		*addr_max;

	addr_max = (((char*)area + area->size_total)
		- (area->size_data + sizeof(t_metadata)));
	new_bloc = (t_metadata*)((char*)bloc + sizeof(t_metadata)
		+ bloc->size_total);
	if ((char*)new_bloc > addr_max)
	{
		area->free = 0;
		return (0);
	}
	new_bloc->size_total = 0;
	new_bloc->next = NULL;
	new_bloc->prev_area = area;
	new_bloc->magic_number = MAGIC_NUMBER_BLOC;
	new_bloc->free = 1;
	new_bloc->size_data = area->size_data;
//	if (size <= SMALL) // Avant dans update_metadata
//		bloc->next = bloc + size;
	bloc->next = new_bloc;
	bloc->size_data = bloc->size_total;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/16 15:01:22 by gperroch         ###   ########.fr       */
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

int				ft_new_area(t_metadata *start, t_metadata **area, size_t size)
{
	char		*cursor;
	t_metadata	*new_area;
	t_metadata	*tmp;
	size_t		size_total;
	t_metadata	first_bloc;

	size_total = (size <= TINY) ? AREA_TINY : AREA_SMALL;
	size_total = (size > TINY && size <= SMALL) ? AREA_SMALL : size_total;
	size_total = (size > SMALL) ?
		(size + sizeof(t_metadata) + sizeof(t_metadata)) : size_total;
	new_area = NULL;
	new_area = mmap(NULL, size_total, PROT_READ | PROT_WRITE |
		PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!new_area)
		return (0);
	ft_init_new_area(new_area, size_total, size);
	if (start)
	{
		tmp = start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_area;
		new_area->prev_area = tmp;
	}
	*area = new_area;
	// Puis ajout du premier bloc vierge.
	ft_memset(&first_bloc, 0, sizeof(t_metadata));
	cursor = (char*)((char*)new_area + sizeof(t_metadata));
	first_bloc.magic_number = MAGIC_NUMBER_BLOC;
	first_bloc.prev_area = new_area;
	first_bloc.size_data = new_area->size_data;
	first_bloc.next = NULL;
	first_bloc.free = 1;
	*((t_metadata*)cursor) = first_bloc;
	return (1);
}

void			ft_init_new_area(t_metadata *new_area, size_t size_total,
	size_t size)
{
	new_area->prev_area = NULL;
	new_area->size_total = size_total;
	new_area->size_data = (size <= TINY) ? TINY : SMALL;
	new_area->size_data = (size > SMALL) ? size : new_area->size_data;
	new_area->free = (size > SMALL) ? 0 : 1;
	new_area->magic_number = MAGIC_NUMBER_AREA;
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

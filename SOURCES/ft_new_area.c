/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_area.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:53:26 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 10:07:38 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				ft_new_area(t_metadata *start, t_metadata **area, size_t size)
{
	char		*cursor;
	t_metadata	*new_area;
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
		ft_add_to_last_area(start, new_area);
	*area = new_area;
	ft_init_first_bloc(&first_bloc, new_area);
	cursor = (char*)((char*)new_area + sizeof(t_metadata));
	*((t_metadata*)cursor) = first_bloc;
	return (1);
}

static	void	ft_init_first_bloc(t_metadata *first_bloc, t_metadata *new_area)
{
	ft_memset(first_bloc, 0, sizeof(t_metadata));
	first_bloc->magic_number = MAGIC_NUMBER_BLOC;
	first_bloc->prev_area = new_area;
	first_bloc->size_data = new_area->size_data;
	first_bloc->next = NULL;
	first_bloc->free = 1;
}

static void		ft_init_new_area(t_metadata *new_area, size_t size_total,
	size_t size)
{
	new_area->prev_area = NULL;
	new_area->size_total = size_total;
	new_area->size_data = (size <= TINY) ? TINY : SMALL;
	new_area->size_data = (size > SMALL) ? size : new_area->size_data;
	new_area->free = (size > SMALL) ? 0 : 1;
	new_area->magic_number = MAGIC_NUMBER_AREA;
}

static void		ft_add_to_last_area(t_metadata *start, t_metadata *new_area)
{
	t_metadata	*tmp;

	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_area;
	new_area->prev_area = tmp;
}

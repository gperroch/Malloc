/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:57:43 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 15:02:12 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
	t_metadata	*bloc;
	t_metadata	*next_bloc;
	size_t		size_total;

	if (!ptr || (ptr && !size))
		return (ft_new_allocation(ptr, size));
	bloc = ptr - sizeof(t_metadata);
	if (bloc->magic_number != MAGIC_NUMBER_BLOC || bloc->free)
		return (NULL);
	if (bloc->size_total >= size)
		return (ptr);
	size_total = bloc->size_total;
	next_bloc = bloc->next;
	ft_calcul_size_available(&next_bloc, &size_total, size, bloc);
	if (size_total < size)
		return (ft_new_allocation(ptr, size));
	bloc->size_total = size_total;
	bloc->size_data = size_total;
	if (size_total >= size + sizeof(t_metadata) + 1)
		ft_add_extra_bloc(ptr, size, size_total, bloc);
	return (ptr);
}

int				ft_calcul_size_available(t_metadata **next_bloc,
	size_t *size_total, size_t size, t_metadata *bloc)
{
	while (*next_bloc && (*next_bloc)->magic_number == MAGIC_NUMBER_BLOC
		&& (*next_bloc)->free && *size_total < size)
	{
		*size_total += (*next_bloc)->size_total + sizeof(t_metadata);
		if (!((*next_bloc)->next))
			*size_total += (bloc->prev_area->size_total) - (((char*)(*next_bloc)
			+ (*next_bloc)->size_total) - (char*)bloc->prev_area);
		*next_bloc = (*next_bloc)->next;
	}
	return (0);
}

void			*ft_new_allocation(void *ptr, size_t size)
{
	void		*new_alloc;
	t_metadata	*bloc;

	new_alloc = malloc(size);
	if (ptr)
	{
		bloc = ptr - sizeof(t_metadata);
		ft_memcpy(new_alloc, ptr, bloc->size_total);
		free(ptr);
	}
	return (new_alloc);
}

int				ft_add_extra_bloc(void *ptr, size_t size, size_t size_total,
	t_metadata *bloc)
{
	t_metadata	*extra_bloc_addr;

	extra_bloc_addr = (t_metadata*)((char*)ptr + size);
	extra_bloc_addr->size_total = size_total - (size + sizeof(t_metadata));
	extra_bloc_addr->next = NULL;
	extra_bloc_addr->prev_area = bloc->prev_area;
	extra_bloc_addr->magic_number = MAGIC_NUMBER_BLOC;
	extra_bloc_addr->free = 1;
	extra_bloc_addr->size_data = (bloc->prev_area)->size_data;
	bloc->size_total = size;
	bloc->next = extra_bloc_addr;
	return (0);
}

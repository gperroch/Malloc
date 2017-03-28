/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/28 11:01:32 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            *malloc(size_t size)
{
	static void	*start = NULL;
	void        **tmp = NULL;
	t_area		*ptr_area = NULL;
	t_block		*ptr_block = NULL;

	if (!start)
		start = ft_mapping(start, size);
	if (size == 0)
		return (start); // !! A ENLEVER
	ptr_area = start;

	printf("MAPPING DE START\n");
	dump_mem(start, 256);

	while (!ptr_block)
	{
		ptr_area = ft_find_next_suitable_area(ptr_area, size);
		ptr_block = ft_find_next_suitable_block(ptr_area, size);
		if (ptr_block->size >= size && ptr_block->free)
			ptr_block->free = 0;
		else
		{
			ptr_block = NULL;
            ptr_area = ptr_area->next ? ptr_area->next : ft_mapping(ptr_area, size);
		}
	}
	return ((char *)ptr_block + sizeof(t_block));
}

static t_area	*ft_find_next_suitable_area(t_area *area, size_t size)
{
	// Trouver la zone appropriee, sinon en cree une nouvelle
	while ((area->size_data < size || !area->free) && area->next)
		area = area->next;
    if ((area->size_data < size || !area->free) && !area->next)
    {
        area->next = ft_mapping(area->next, size);
	
		printf("NOUVELLE AREA\n");
		dump_mem(area, 256);
    
		area = area->next;
    }

	return (area);
}

static t_block	*ft_find_next_suitable_block(t_area *area, size_t size)
{
	t_block		*ptr_block;

	// Trouver un block libre
	ptr_block = (t_block *)((char *)area + sizeof(t_block)); //sizeof(t_area) ?
	while ((ptr_block->size < size || !ptr_block->free) && ptr_block->next)
		ptr_block = ptr_block->next;

    // ATTENTION : verifier que le nouveau bloc de data ne depasse pas de la zone
    if ((ptr_block->size < size || !ptr_block->free) && !ptr_block->next && area->size_area + (long)area - ((long)ptr_block + sizeof(t_block)) >= size && area->size_area + (long)area - ((long)ptr_block + sizeof(t_block)) < area->size_area)
	{
		ptr_block->next = (t_block *)((char *)ptr_block + ptr_block->size + sizeof(t_block));
		ptr_block = ptr_block->next;
		ft_new_metadata(ptr_block, size);

		printf("NOUVELLES METADATA\n");
		dump_mem(area, 256);
	}

	return (ptr_block);
}

int		ft_new_metadata(void *addr_block, int size)
{
	t_block		metadata;

	metadata.size = size;
	metadata.free = 1;
	metadata.next = NULL;
	*(t_block *)addr_block = metadata;
	return (0);
}

static int		ft_find_block(void **ptr, size_t size)
{
	t_block		*block;

	if (!*ptr)
		return (-1);
	block = *ptr + sizeof(t_area);
	while ((block->size < size || !block->free) && block->next)
		block = block->next;
	if ((block->size < size || !block->free) && !block->next) // Aucun block libre
	{
		if ((void *)((block + sizeof(t_block)) - ((t_area *)ptr)->size_area) >= (void *)(size + sizeof(t_block)))
		{
			ft_new_metadata((block + sizeof(t_block) + block->size), size);
			block->next = block + sizeof(t_block) + block->size;
			block = block->next;
		}
		else
		return (-1);
	}
	*ptr = (char *)block + sizeof(t_block);
	block->free = 0;
	return (1);
}

static t_area	*ft_mapping(void *ptr, size_t size)
{
	void		*start;
	t_area		first_area;
	t_block		block;
	int			size_area;

	size_area = (size <= TINY) ? AREA_TINY : AREA_SMALL;
	size_area = (size > TINY && size <= SMALL) ? AREA_SMALL : size_area;
	size_area = (size > SMALL) ? (size + sizeof(t_area) + sizeof(t_block)) : size_area;
	start = mmap(ptr, size_area, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_SHARED, -1, 0);
	ptr = start;
	ft_bzero(&first_area.size_area, 32);
	first_area.size_area = size_area;
	first_area.size_data = (size <= TINY) ? TINY : SMALL;
	first_area.size_data = (size > SMALL) ? size : first_area.size_data;
	first_area.next = NULL;
	first_area.free = (size > SMALL) ? 0 : 1;
	*(t_area *)start = first_area;
	ft_bzero(&block.size, 32);
	block.size = size;
	block.next = NULL;
	block.free = 1;
	*((t_block *)(start + sizeof(t_area))) = block;

	return (start);
}

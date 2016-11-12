/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2016/05/18 16:55:41 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("|\\-/| DEBUG %d |\\-/|\n", x);

int main(void)
{
	void *ptr1;
	void *ptr2;

	printf("sizeof(t_block) = %lu ||| sizeof(t_area) = %lu\n", sizeof(t_block), sizeof(t_area));
	ptr1 = malloc(128);
	printf("malloc1 = %p\n", ptr1);
	ptr2 = malloc(3000);
	printf("malloc2 = %p\n", ptr2);
	return 0;
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
/*	if (block->size >= (size + 4 + sizeof(t_block)))
	{
		ft_new_metadata((*ptr + size), (block->size - size - sizeof(t_block)));
		((t_block *)(*ptr + size))->next = block->next;
		block->next = ((t_block *)(*ptr + size));
		block->size = size;
	}*/
	return (1);
}
/*
static void		ft_segmentation(void *start)
{
	printf("kek");
}
*/
static t_area	*ft_mapping(void *ptr, size_t size)
{
	void		*start;
	t_area		first_area;
	t_block		block;
	int			size_area;

	size_area = (size == TINY) ? AREA_TINY : AREA_SMALL;
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

void			*malloc(size_t size)
{
	static void	*start = NULL;
	void		**tmp;
	t_area		*ptr_area;
	t_block		*ptr_block;

	if (!start)
		start = ft_mapping(start, size);
	if (size == 0)
		return (start);
	ptr_area = start;
dump_mem(ptr_area, 512);
	// Trouver la zone appropriee
	while ((ptr_area->size_data < size || !ptr_area->free) && ptr_area->next)
		ptr_area = ptr_area->next;
	// mmap une nouvelle zone si necessaire
	if ((ptr_area->size_data < size || !ptr_area->free) && !ptr_area->next)
	{
		ptr_area->next = ft_mapping(ptr_area->next, size);
		ptr_area = ptr_area->next;
	}
	// Trouver un block libre
	ptr_block = (t_block *)((char *)ptr_area + sizeof(t_block));
	while ((ptr_block->size < size || !ptr_block->free) && ptr_block->next)
		ptr_block = ptr_block->next;
	if ((ptr_block->size < size || !ptr_block->free) && !ptr_block->next)
	{
		ptr_block->next = (t_block *)((char *)ptr_block + ptr_block->size + sizeof(t_block));
		ptr_block = ptr_block->next;
		ft_new_metadata(ptr_block, size);
	}
	if (ptr_block->size <= size && ptr_block->free)
		ptr_block->free = 0;
	// mmap une nouvelle zone si aucun block n'est libre dans celle-ci
dump_mem(ptr_area, 512);
	return ((char *)ptr_block + sizeof(t_block));
}

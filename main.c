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

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int main(int argc, char **argv)
{
	void *ptr1;
	void *ptr2;
	int i = 0;

	printf("sizeof(void*) = %lu, sizeof(size_t) = %lu, sizeof(t_area) = %lu\n", sizeof(void*), sizeof(size_t), sizeof(t_area));
	printf("getpagesize() = %d\n", getpagesize());
	printf("TINY size_area_v1 = %lu, size_area_v2 = %lu\n", AREA_TINY, AREA_TINY_V2);
	printf("TINY Multiples : v1 = %5f, v2 = %5f\n", (double)((double)AREA_TINY / (double)getpagesize()), (double)((double)AREA_TINY_V2 / (double)getpagesize()));
	printf("SMALL size_area_v1 = %lu, size_area_v2 = %lu\n", AREA_SMALL, AREA_SMALL_V2);
	printf("SMALL Multiples : v1 = %5f, v2 = %5f\n", (double)((double)AREA_SMALL / (double)getpagesize()), (double)((double)AREA_SMALL_V2 / (double)getpagesize()));
	while (i++ > 10)
	{
		printf("malloc %d = %p\n", i, ptr1);
		ptr1 = malloc(atoi(argv[1]));
		dump_mem(ptr1 - (i * (32 + atoi(argv[1])) + 32), 256);
	}
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

static t_area	*ft_mapping(void *ptr, size_t size)
{
	void		*start;
	t_area		first_area;
	t_block		block;
	int			size_area;

	// Sélection de la taille à allouer (TINY, SMALL ou custom pour les plus grandes)
	size_area = (size <= TINY) ? AREA_TINY : AREA_SMALL;
	size_area = (size > TINY && size <= SMALL) ? AREA_SMALL : size_area;
	size_area = (size > SMALL) ? (size + sizeof(t_area) + sizeof(t_block)) : size_area;

	/*
	* ptr: 			start of the mapped area
	* size_area:	max length (in bytes) mapped
	* PROT_READ:	pages may be read
	* PROT_WRITE:	pages may be written
	* PROT_EXEC:	pages may be executed
	* MAP_ANON:		anonymous memory not associated with any specific file
	* MAP_SHARED:	modifications are shared
	* -1:			file descriptor of the object to be mapped. -1 means no specific object
	* 0:			offset
	*/
	start = mmap(ptr, size_area, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_SHARED, -1, 0);

	ptr = start;

	//Initialisation de la structure de la zone
	ft_bzero(&first_area.size_area, 32);
	first_area.size_area = size_area;
	first_area.size_data = (size <= TINY) ? TINY : SMALL;
	first_area.size_data = (size > SMALL) ? size : first_area.size_data;
	first_area.next = NULL;
	first_area.free = (size > SMALL) ? 0 : 1;
	*(t_area *)start = first_area;

	//Initialisation de la strucutre du bloc de donnees en question
	//Mutualisation possible avec ft_new_metadata
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
	void		**tmp = NULL;
	t_area		*ptr_area = NULL;
	t_block		*ptr_block = NULL;

	// Premier appel. Initialisation de la première zone.
	if (!start)
	{
		DEBUG("Premier passage. Mapping de la première zone et du premier bloc.");
		start = ft_mapping(start, size);
	}
	if (size == 0)
	{
		DEBUG("size == null. Return(start)");
		return (start);
	}
	ptr_area = start;

	while (!ptr_block)
	{
		ptr_area = ft_find_next_suitable_area(ptr_area, size);

		// mmap une nouvelle zone si necessaire
		if ((ptr_area->size_data < size || !ptr_area->free) && !ptr_area->next)
			ptr_area = ft_map_new_area(ptr_area, size);

		ptr_block = ft_find_next_suitable_block(ptr_area, size);

		//Ajout d'un nouveau bloc dans la zone si necessaire
		// ATTENTION : verifier que le nouveau bloc de data ne depasse pas de la zone
		printf("[DEBUG] Taille restante : %ld + %ld - (%ld + %ld) = %ld\n", ptr_area->size_area, (long)ptr_area, (long)ptr_block, sizeof(t_block), ptr_area->size_area + (long)ptr_area - ((long)ptr_block + sizeof(t_block)));
		if ((ptr_block->size < size || !ptr_block->free) && !ptr_block->next && ptr_area->size_area + (long)ptr_area - ((long)ptr_block + sizeof(t_block)) >= size && ptr_area->size_area + (long)ptr_area - ((long)ptr_block + sizeof(t_block)) < ptr_area->size_area)
		{
			DEBUG("Ajout d'un nouveau bloc.");
			ptr_block->next = (t_block *)((char *)ptr_block + ptr_block->size + sizeof(t_block));
			ptr_block = ptr_block->next;
			ft_new_metadata(ptr_block, size);
		}

		//???
		if (ptr_block->size >= size && ptr_block->free)
		{
			DEBUG("Bloc de taille suffisante et libre trouvé.");
			ptr_block->free = 0;
		}
		else
		{
			DEBUG("Aucun bloc de taille suffisante et disponible dans cette zone. Passage à la zone suivante.");
			ptr_block = NULL;
			// mmap une nouvelle zone si aucun block n'est libre dans celle-ci
			if (ptr_area->next)
				ptr_area = ptr_area->next;
			else
				ptr_area = ft_map_new_area(ptr_area, size);
		}
	}
	return ((char *)ptr_block + sizeof(t_block));
}

static t_area	*ft_find_next_suitable_area(t_area *area, size_t size)
{
	DEBUG("Recherche de la zone appropriée.");
	// Trouver la zone appropriee
	while ((area->size_data < size || !area->free) && area->next)
		area = area->next;

	return (area);
}

static t_block	*ft_find_next_suitable_block(t_area *area, size_t size)
{
	t_block		*ptr_block;

	DEBUG("Recherche d'un bloc libre de taille suffisante.");
	// Trouver un block libre
	ptr_block = (t_block *)((char *)area + sizeof(t_block)); //sizeof(t_area) ?
	while ((ptr_block->size < size || !ptr_block->free) && ptr_block->next)
		ptr_block = ptr_block->next;

	return (ptr_block);
}

static t_area	*ft_map_new_area(t_area *area,size_t size)
{
	DEBUG("Mapping d'une nouvelle zone.");
	area->next = ft_mapping(area->next, size);
	area = area->next;

	return (area);
}

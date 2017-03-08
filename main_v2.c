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

	while (i++ < 10)
	{
		printf("malloc %d = %p\n", i, ptr1);
		ptr1 = malloc(atoi(argv[1]));
		dump_mem(ptr1 - (i * (32 + atoi(argv[1])) + 32), 256);
	}
	return 0;
}

static t_area_v2	*ft_mapping(void *ptr, size_t size)
{
	void			*start;
	t_area_v2		first_area;
	t_block			block;
	int				size_area;

	// Sélection de la taille à allouer (TINY, SMALL ou custom pour les plus grandes.
	// Revoir les tailles pour qu'elles soient multiples de 4096. Inclure 4096 dedans idéalement.
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
//	first_area.next = NULL; //Deja initialiser avec ft_bzero
	first_area.metadata = (long)&first_area + sizeof(first_area);
	*(first_area.metadata) = sizeof(t_area) + 100 * (sizeof(void*) + sizeof(size_t)); // Adresse du premier bloc.
	*(t_area *)start = first_area; // Bizarre.

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
		if ((ptr_area->full || ptr_area->size_data < size) && !ptr_area->next)
			ptr_area = ft_map_new_area(ptr_area, size);

		ptr_block = ft_find_next_suitable_block(ptr_area, size);


	}
	return ((char *)ptr_block + sizeof(t_block));
}

static t_area	*ft_find_next_suitable_area(t_area *area, size_t size)
{
	DEBUG("Recherche de la zone appropriée.");
	// Trouver la zone appropriee
	while (!area->full && (area->size_data < size || !area->free) && area->next)
		area = area->next;

	return (area);
}

static t_block	*ft_find_next_suitable_block(t_area *area, size_t size)
{
	t_block		*ptr_block;
	int			count;

	count = -1;
	ptr_block = NULL;
	DEBUG("Recherche d'un bloc libre de taille suffisante.");
	// Trouver un block libre
	while (!ptr_block && ++count < 100)
	{
		if (area->block[count] && !area->size_block[count])
		{
			ptr_block = area->block[count]
			area->size_block[count] = size;
		}
		area->full = count == 99 ? TRUE : FALSE;
	}

	return (ptr_block);
}

static t_area	*ft_map_new_area(t_area *area,size_t size)
{
	DEBUG("Mapping d'une nouvelle zone.");
	area->next = ft_mapping(area->next, size);
	area = area->next;

	return (area);
}

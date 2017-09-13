/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:58:08 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/13 16:02:45 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));

/*
 * Ajouter une verification des magic_number ici ?
 * En cas d’erreur, les fonctions malloc() et realloc() retournent un pointeur
 * NULL.
 * ft_find_area : renvoie 0 si aucune zone n'est disponible.
 * ft_new_area  : cree une nouvelle zone.
 * ft_find_bloc : trouve le premier bloc disponible dans la zone determinee.
 * ft_update_metadata : met a jour les metadata du bloc trouve.
 * ft_add_next_metadata : prepare le prochain bloc si size <= SMALL.
*/

void			*malloc(size_t size)
{
	static void	*start = NULL;
	t_metadata	*area;
	t_metadata	*bloc;

	area = NULL;
	bloc = NULL;
	/* ATTENTION: sans le cast en int, le test malloc(-1) est passant alors
	 * qu'il ne devrait pas l'etre. Probleme de type en size_t et int a regler.
	 * Necessaire pour le malloc(2147483648) aussi.
	*/
	if ((int)size < 0)
		return (NULL);
	if (!ft_find_area(start, &area, size))
	{
		if (!ft_new_area(start, &area, size))
			return (NULL);
		if (!start)
			start = area;
	}
	ft_find_bloc(area, &bloc, size);
	ft_update_metadata(bloc, size); // Cas d'erreurs à faire.
	if (size <= SMALL)
		ft_add_next_metadata(bloc, area);
	return ((void*)bloc + sizeof(t_metadata));
}

int				ft_find_area(void *start, t_metadata **area, size_t size)
{
	t_metadata	*cursor;

	cursor = (void*)start;
	if (!start)
		return (0);
	while ((cursor->size_data < size || !cursor->free) && cursor->next)
		cursor = cursor->next;
	*area = cursor;
	if (cursor->size_data >= size && cursor->free)
		return (1);
	return (0);
}

int				ft_find_bloc(t_metadata *area, t_metadata **bloc, size_t size) // Mutualiser ft_find_bloc et ft_find_area quand bloc et area auront la meme structure. S'assurer du bon fonctionnement avec size_data (au lieu de size_total, pour mutualiser)
{
	t_metadata	*cursor;

	cursor = (void*)area + sizeof(t_metadata);
	while ((cursor->size_total < size || !cursor->free) && cursor->next)
	//while ((cursor->size_data < size || !cursor->free) && cursor->next)
		cursor = cursor->next;
	*bloc = cursor;
	if (cursor->size_total >= size && cursor->free)
	//if (cursor->size_data >= size && cursor->free)
		return (1);
	return (0);
}

int				ft_update_metadata(t_metadata *bloc, size_t size)
{
	bloc->free = 0;
	bloc->size_total = size;
	if (size <= SMALL)
		bloc->next = bloc + size;
	return (0);
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

int				ft_new_area(t_metadata *start, t_metadata **area, size_t size) // Ajout d'une nouvelle zone, soit en première position, soit après la dernière zone trouvée.
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
	first_bloc.free = 0;
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
	new_bloc = (char*)bloc + sizeof(t_metadata) + bloc->size_total;
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
	bloc->next = new_bloc;
	return (1);
}

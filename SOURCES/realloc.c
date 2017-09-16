/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:57:43 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/16 15:02:25 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));
/*
 *
 * Attention : cast les pointeurs en char* avant de les incrémenter. ptr + 1 revient a faire ptr + sizeof(ptr) => CAST EN CHAR* POUR TOUTES LES OPERATIONS SUR LES ADRESSES.
 * En cas d’erreur, les fonctions malloc() et realloc() retournent un pointeur NULL
*/
int				ft_calcul_size_available(t_metadata **next_bloc, int *size_total, int size, t_metadata *bloc);

void 			*realloc(void *ptr, size_t size)
{
	t_metadata	*bloc;
	t_metadata	*next_bloc;
//	t_metadata  last_bloc;
	t_metadata	*last_bloc_addr;
	t_metadata	*new_bloc;
	void 		*new_alloc;
	int			size_total;

	if (!ptr || (ptr && !size))
	{
		new_alloc = malloc(size);
		if (ptr)
			free(ptr);
		return (new_alloc);
	}
	bloc = ptr - sizeof(t_metadata);
	if (bloc->magic_number != MAGIC_NUMBER_BLOC || bloc->free)
		return (NULL);
	if (bloc->size_total >= size)
		return (ptr);
	size_total = bloc->size_total;
	next_bloc = bloc->next;
/*	while (next_bloc && next_bloc->magic_number == MAGIC_NUMBER_BLOC
		&& next_bloc->free && size_total < size)
	{
		size_total += next_bloc->size_total + sizeof(t_metadata);
		if (!(next_bloc->next))
			size_total += (bloc->prev_area->size_total) - (((char*)next_bloc + next_bloc->size_total) - (char*)bloc->prev_area);
		next_bloc = next_bloc->next;
	}*/
	ft_calcul_size_available(&next_bloc, &size_total, size, bloc);

	if (size_total < size) // Il n'y a pas suffisament de bloc disponibles. Malloc d'un nouveau bloc, copie des donnees. // ATTENTION aux zones qui ne sont pas encore entierement mapped par des metadata.
	{
		new_alloc = malloc(size);
		new_bloc = (t_metadata*)((char*)new_alloc - sizeof(t_metadata));
		ft_memcpy(new_alloc, ptr, bloc->size_total);
		bloc->free = 1;
		return (new_bloc);
	}
	else if (size_total >= size) // Suffisament de blocs libres sont consecutifs.
	{
		bloc->size_total = size_total;
		bloc->size_data = size_total;
	}

	if (size_total >= size + sizeof(t_metadata) + 1) // Il reste la place pour un bloc free de 1 octet. // On insere de nouvelles metadata pour rendre ce bloc disponible et ne pas prendre trop de place avec notre reallocation.
	{
		last_bloc_addr = (t_metadata*)((char*)ptr + size);
		last_bloc_addr->size_total = size_total - (size + sizeof(t_metadata));
		last_bloc_addr->next = 0; // A verifier
		last_bloc_addr->prev_area = bloc->prev_area;
		last_bloc_addr->magic_number = MAGIC_NUMBER_BLOC;
		last_bloc_addr->free = 1;
		last_bloc_addr->size_data = last_bloc_addr->size_total; // Ou rediviser ce nouveau bloc en blocs de tailles max correspond a la size_data de la zone ?
		bloc->size_total = size; // La place excedante a ete remplacee par un bloc vierge, la taille total du bloc realloue correspond parfaitement a la taille demandee.
		bloc->next = last_bloc_addr;
	}
	return (ptr);
}

int				ft_calcul_size_available(t_metadata **next_bloc, int *size_total, int size, t_metadata *bloc)
{
	while (*next_bloc && (*next_bloc)->magic_number == MAGIC_NUMBER_BLOC
		&& (*next_bloc)->free && *size_total < size)
	{
		*size_total += (*next_bloc)->size_total + sizeof(t_metadata);
		if (!((*next_bloc)->next))
			*size_total += (bloc->prev_area->size_total) - (((char*)(*next_bloc) + (*next_bloc)->size_total) - (char*)bloc->prev_area);
		*next_bloc = (*next_bloc)->next;
	}
	return (0);
}

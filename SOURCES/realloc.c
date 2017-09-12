/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:57:43 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/12 18:17:07 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));
/*
 *
 * Attention : cast les pointeurs en char* avant de les incrémenter. ptr + 1 revient a faire ptr + sizeof(ptr)
 * En cas d’erreur, les fonctions malloc() et realloc() retournent un pointeur NULL
*/

void 			*realloc(void *ptr, size_t size)
{
	t_metadata	*bloc;
	t_metadata	*next_bloc;
	t_metadata  last_bloc;
	t_metadata	*last_bloc_addr;
	t_metadata	*new_bloc;
	void 		*new_alloc;
	int			size_total;

	if (!ptr)
		return (malloc(size));
	if (ptr && !size)
	{
		new_alloc = malloc(size);
		free(ptr);
		return (new_alloc);
	}
	// !ptr && size : call malloc(size)
	// !ptr && !size : call malloc(0) aka malloc(size)
	// ptr && size : reallocation normale
	// ptr && !size : call malloc(0) et free(ptr)
	// PROCESSUS DE REALLOCATION : ptr && size
	bloc = ptr - sizeof(t_metadata);
	if (bloc->magic_number != MAGIC_NUMBER_BLOC || bloc->free)
		return (NULL);
	if (bloc->size_total >= size)  // La taille demandee est inferieure a la taille disponible.
		return (ptr);

	size_total = bloc->size_total;
	next_bloc = bloc->next;
	while (next_bloc && next_bloc->magic_number == MAGIC_NUMBER_BLOC
		&& next_bloc->free && size_total < size) // Cumule du nombre de blocs disponibles a la suite du premier.
	{
		size_total += next_bloc->size_total + sizeof(t_metadata);
		if (!(next_bloc->next)) // La zone n'est pas entierement mapped par des metadata, une partie reste vierge. On ajoute la taille de cette partie a la size_total.
			size_total += (bloc->prev_area->size_total) - ((next_bloc + next_bloc->size_total) - bloc->prev_area); // Prendre la valeur absolue du deuxieme membre.
		next_bloc = next_bloc->next;
	}

	if (size_total < size) // Il n'y a pas suffisament de bloc disponibles. Malloc d'un nouveau bloc, copie des donnees. // ATTENTION aux zones qui ne sont pas encore entierement mapped par des metadata.
	{
		new_alloc = malloc(size);
		new_bloc = new_alloc - sizeof(t_metadata);
		ft_memcpy(new_alloc, ptr, bloc->size_total);
		bloc->free = 1;
		new_bloc->size_total = size;
		new_bloc->next = NULL;
		new_bloc->prev_area = (char*)new_bloc - sizeof(t_metadata); // AJOUTER la verification du magic_number de l'area. ET modifier les metadata de cette area (area_prev par exemple).
		// POURQUOI LE NEW_BLOC DOIT ETRE INITIALISE ICI, POURQUOI NE L'EST IL PAS CORRECTEMENT LORS DE L'APPEL DE MALLOC ???

		return (new_bloc);
	}
	else if (size_total >= size) // Suffisament de blocs libres sont consecutifs.
		bloc->size_total = size_total;

	if (size_total >= size + sizeof(t_metadata) + 1) // Il reste la place pour un bloc free de 1 octet. // On insere de nouvelles metadata pour rendre ce bloc disponible et ne pas prendre trop de place avec notre reallocation.
	{
		last_bloc.size_total = size_total - (size + sizeof(t_metadata));
		last_bloc.next = 0; // A verifier
		last_bloc.prev_area = bloc->prev_area;
		last_bloc.magic_number = MAGIC_NUMBER_BLOC;
		last_bloc.free = 1;
		last_bloc.size_data = last_bloc.size_total; // Ou rediviser ce nouveau bloc en blocs de tailles max correspond a la size_data de la zone ?
		// Initialisation du last_bloc a faire ici.
		last_bloc_addr = (char*)ptr + size;
		*last_bloc_addr = last_bloc;
		bloc->size_total = size; // La place excedante a ete remplacee par un bloc vierge, la taille total du bloc realloue correspond parfaitement a la taille demandee.
		bloc->next = last_bloc_addr;
	}
	return (ptr);
}

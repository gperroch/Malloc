/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:57:43 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/05 18:04:34 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
 *
 * Attention : cast les pointeurs en char* avant de les incrémenter. ptr + 1 revient a faire ptr + sizeof(ptr)
 *
*/

void 			*realloc(void *ptr, size_t size)
{
	t_metadata	*bloc;
	t_metadata	*next_bloc;
	t_metadata  last_bloc;
	t_metadata	*last_bloc_addr;
	void 		*new_bloc;
	int			size_total;

	if (!ptr)
		printf("ptr null\n"); // If ptr is NULL, realloc() is identical to a call to malloc() for size bytes

	if (!size && !ptr)
		return (NULL); // If size is zero and ptr is not NULL, a new, minimum sized object is allocated and the original object is freed

	bloc = ptr - sizeof(t_metadata);
	if (bloc->magic_number != MAGIC_NUMBER_BLOC)
	{
		printf("PTR N'EST PAS LE DEBUT D'UN BLOC.\n");
		// Comment gerer cela ? Renvoyer NULL ou reculer jusqu'au premier amgic_number ? // A voir comment le vrai realloc fonctionne.
		return (NULL);
	}
	if (bloc->size_total >= size)
		return (ptr);

	size_total = bloc->size_total;
	next_bloc = bloc->next;
	while (next_bloc && next_bloc->magic_number == MAGIC_NUMBER_BLOC
		&& next_bloc->free && size_total < size)
	{
		size_total += next_bloc->size_total + sizeof(t_metadata);
		next_bloc = next_bloc->next;
	}

	if (size_total < size || !ptr)
	{
		new_bloc = malloc(size);
		ft_memcpy(new_bloc, ptr, bloc->size_total);
		return (new_bloc);
	}

	if (size_total >= size)
	{
		bloc->size_total = size_total;
		printf("TAILLE SUFFISANTE\n");
	}
	else
	{
		printf("TAILLE INSUFFISANTE\n");
		// Malloc puis return.
	}

	printf("size_total:%d >= (size + sizeof(t_metadata) + 1):%d\n", size_total, size + sizeof(t_metadata) + 1);
	if (size_total >= size + sizeof(t_metadata) + 1) // Il reste la place pour un bloc free de 1 octet. // On insere de nouvelles metadata pour rendre ce bloc disponible et ne pas prendre trop de place avec notre reallocation.
	{
		// Initialisation du last_bloc a faire ici.
		printf("CREATION DU LAST_BLOC\n");
		ft_memset(&last_bloc, 255, sizeof(t_metadata));
		last_bloc_addr = ptr + size;
		*last_bloc_addr = last_bloc;
		bloc->size_total = size; // La place excedante a ete remplacee par un bloc vierge, la taille total du bloc realloue correspond parfaitement a la taille demandee.
	}
	return (NULL);
}






/*



















// Vieille version
void			*realloc(void *ptr, size_t size)
{
	t_metadata		*tmp;
	t_metadata		*bloc_initial;
	t_metadata		*next_bloc;
	t_metadata		*last_bloc;
	int				size_total;
	int				nb_bloc;

	//printf("REALLOC: ptr = %p\tsize = %zu\n", ptr, size);
	bloc_initial = ptr - sizeof(t_metadata);
	//printf("block_initial = %p\t block_initial->size = %zu\t sizeof(t_block) = %zu\n", block_initial, block_initial->size, sizeof(t_block));
	//(1) next_bloc = (t_block*)((char*)block_initial + sizeof(t_block) + block_initial->size); // ptr + block_initial->size;
	next_bloc = (char*)bloc_initial->next + sizeof(t_metadata);
	//printf("next_block = %p\n", next_block);
	size_total = bloc_initial->size_total;
	nb_bloc = 0;
	while (next_bloc && next_bloc->free == 1 && size_total < size)
	{
		size_total += next_bloc->size_total + sizeof(t_metadata);
		nb_bloc++;
		next_bloc = next_bloc->next;
		//printf("next_block = %p\n", next_block);
	}
	//printf("next_block = %p\n", next_block);
	last_bloc = next_bloc;
	//printf("last_block = %p\n", last_block);
	//(1) next_block = (t_block*)((char*)block_initial + sizeof(t_block) + block_initial->size); // ptr + block_initial->size;
	next_bloc = (char*)bloc_initial->next + sizeof(t_metadata);
	//printf("size total = %d\tsize = %zu\tnext_block = %p\n", size_total, size, next_block);
	if (size_total >= size)
	{
		//printf("nb_block = %d\n", nb_block);
		while (nb_bloc > 0)
		{
			tmp = next_bloc;
			next_bloc = next_bloc->next;
	//		ft_bzero(tmp, sizeof(t_metadata)); // Remise a zero de tout le block (header + metadata ?) ou aucune remise a zero ? // Aucune remise a zero, modification des metadata uniquement. //Pas de remise a zero, on ne touche pas a l'etat de la memoire en dehors des metadata.
			nb_bloc--;
		}
		if (size_total - size >= sizeof(t_metadata) + 4) // +4 ? pourquoi pas + TINY ou SMALL ? Vérifier qu'on a la place pour un nouveau block (header + data) ? // Sert a preparer un nouveau bloc vierge a la fin de la reallocation.
		{
			tmp = ptr + size;
			// ft_new_metadata a revoir. Remplacer par add_next_metadata ?
		//	ft_new_metadata(tmp, size_total - size - sizeof(t_block), NULL);
		//	//printf("new block at %p, size %lu\n", (ptr + size), size_total - size - sizeof(t_block));
		//	tmp->free = 1;
		//	tmp->next = next_bloc;
		//	//ft_bzero(&tmp->data[0], 16);
		//	bloc_initial->size_total = size;
		}
		else
			bloc_initial->size_total = size_total;
		bloc_initial->next = last_bloc;
		return (ptr);
	}
	// Pas de place, re-malloc
	bloc_initial->free = 1;
	tmp = malloc(size);
	ft_memcpy(tmp, ptr, size);
	//ft_bzero(ptr, block_initial->size); //Pas de remise a zero, on ne touche pas a l'etat de la memoire en dehors des metadata.
	return (tmp);
}



*/

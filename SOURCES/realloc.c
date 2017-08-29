/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:57:43 by gperroch          #+#    #+#             */
/*   Updated: 2017/08/29 14:41:57 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
 *
 * Attention : cast les pointeurs en char* avant de les incrémenter. ptr + 1 revient a faire ptr + sizeof(ptr)
 *
*/


/* Vieille version */
void			*realloc(void *ptr, size_t size)
{
	t_block		*tmp;
	t_block		*block_initial;
	t_block		*next_block;
	t_block		*last_block;
	int			size_total;
	int			nb_block;

	//printf("REALLOC: ptr = %p\tsize = %zu\n", ptr, size);
	block_initial = ptr - sizeof(t_block);
	//printf("block_initial = %p\t block_initial->size = %zu\t sizeof(t_block) = %zu\n", block_initial, block_initial->size, sizeof(t_block));
	next_block = (t_block*)((char*)block_initial + sizeof(t_block) + block_initial->size); // ptr + block_initial->size;
	//printf("next_block = %p\n", next_block);
	size_total = block_initial->size;
	nb_block = 0;
	while (next_block && next_block->free == 1 && size_total < size)
	{
		size_total += next_block->size + sizeof(t_block);
		nb_block++;
		next_block = next_block->next;
		//printf("next_block = %p\n", next_block);
	}
	//printf("next_block = %p\n", next_block);
	last_block = next_block;
	//printf("last_block = %p\n", last_block);
	next_block = (t_block*)((char*)block_initial + sizeof(t_block) + block_initial->size); // ptr + block_initial->size;
	//printf("size total = %d\tsize = %zu\tnext_block = %p\n", size_total, size, next_block);
	if (size_total >= size)
	{
		//printf("nb_block = %d\n", nb_block);
		while (nb_block > 0)
		{
			tmp = next_block;
			next_block = next_block->next;
			ft_bzero(tmp, sizeof(t_block)); // Remise a zero de tout le block (header + metadata ?) ou aucune remise a zero ?
			nb_block--;
		}
		if (size_total - size >= sizeof(t_block) + 4) // +4 ? pourquoi pas + TINY ou SMALL ? Vérifier qu'on a la place pour un nouveau block (header + data) ?
		{
			tmp = ptr + size;
			ft_new_metadata(tmp, size_total - size - sizeof(t_block), NULL);
			//printf("new block at %p, size %lu\n", (ptr + size), size_total - size - sizeof(t_block));
			tmp->free = 1;
			tmp->next = next_block;
			ft_bzero(&tmp->data[0], 16);
			block_initial->size = size;
		}
		else
			block_initial->size = size_total;
		block_initial->next = last_block;
		return (ptr);
	}
	// Pas de place, re-malloc
	block_initial->free = 1;
	tmp = malloc(size);
	ft_memcpy(tmp, ptr, size);
	ft_bzero(ptr, block_initial->size);
	return (tmp);
}


/* Nouvelle version /

void			*realloc(void *ptr, size_t size)
{
	t_block		*block;

	block = ptr - sizeof(t_block);
}

/ */

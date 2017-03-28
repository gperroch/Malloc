/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:57:43 by gperroch          #+#    #+#             */
/*   Updated: 2016/05/17 18:08:08 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
	t_block		*tmp;
	t_block		*block;
	t_block		*next_block;
	int			size_total;
	int			nb_block;

	block = ptr - sizeof(t_block);
	next_block = ptr + block->size;
	size_total = block->size;
	nb_block = 0;
	while (next_block->free == 1 && next_block && size_total < size)
	{
		size_total += next_block->size + sizeof(t_block);
		nb_block++;
		next_block = next_block->next;
	}
	next_block = ptr + block->size;
	if (size_total >= size)
	{
		while (nb_block > 0)
		{
			tmp = next_block;
			next_block = next_block->next;
			ft_bzero(tmp, sizeof(t_block));
			nb_block--;
		}
		if (size_total - size >= sizeof(t_block) + 4)
		{
			tmp = ptr + size;
			ft_new_metadata(tmp, size_total - size - sizeof(t_block));
			printf("new block at %p, size %lu\n", (ptr + size), size_total - size - sizeof(t_block));
			tmp->free = 1;
			tmp->next = next_block;
			ft_bzero(&tmp->data[0], 16);
			block->size = size;
		}
		else
			block->size = size_total;
		return (ptr);
	}
	block->free = 1;
	tmp = malloc(size);
	ft_memcpy(tmp, ptr, size);
	ft_bzero(ptr, block->size);
	return (tmp);
}

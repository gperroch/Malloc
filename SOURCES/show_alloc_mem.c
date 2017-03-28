/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:52:45 by gperroch          #+#    #+#             */
/*   Updated: 2016/05/17 18:09:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			show_alloc_mem(void)
{
	void		*ptr;
	t_block		*block;

	ptr = malloc(0);
	block = (t_block *)ptr;
	while (block)
	{
		if (block->free == 0 && block->size > 0)
		{
			printf("%p - %p : %zu octets\n", ((char *)block + sizeof(t_block)), block->next, block->size);
//			ft_printf("%p - %p : %zu octets\n", ((char *)block + sizeof(t_block)), block->next, block->size);
//			printf("block(%p)->free = %d\n", block, block->free);
			//ft_printf("block(%p)->free = %d\n", block, block->free);

// Probleme avec ft_printf qui vient remettre la memoire a zero, free dans le cas precedent
		}
		block = block->next;
	}
}

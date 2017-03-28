/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:30:24 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/20 10:26:37 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			free(void *ptr)
{
	t_area		*start;
	t_block		*block;

	if (!ptr)
		return ;

	start = malloc(0);
	while (start->next && (void*)start->next < ptr)
		start = start->next;
	block = start + sizeof(t_area);
	while (block->next && (void*)block->next < ptr)
		block = block->next;

	if ((void*)(block + block->size + sizeof(t_block)) > ptr)
	{
		block = ptr - sizeof(t_block);
		block->free = 1;		
	}
}

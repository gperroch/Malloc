/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:30:24 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/28 11:06:33 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			free(void *ptr)
{
	t_area		*start;
	t_block		*block;

	if (!ptr)
		return ;

//	block = ptr - sizeof(t_block);

//	if ((void*)(block + block->size + sizeof(t_block)) > ptr)
//	{
		block = ptr - sizeof(t_block);
		block->free = 1;		
//	}
}

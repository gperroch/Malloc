/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:30:24 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/05 15:09:04 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// ENLEVER LES 2 PRINTF DE DEBUG

void			free(void *ptr)
{
	t_metadata	*bloc;

	if (!ptr)
		return ;

	bloc = ptr - sizeof(t_metadata);
	if (bloc->magic_number != MAGIC_NUMBER_BLOC)
	{
		printf("WRONG NUMBER. ptr:%p bloc:%p\n", ptr, bloc);
		return ;
	}
	printf("GOOD NUMBER. ptr:%p bloc:%p\n", ptr, bloc);
	bloc->free = 1;
}

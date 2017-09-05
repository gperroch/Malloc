/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/05 16:04:37 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*start;
	void	*tmp;
	t_metadata 	*cursor;
	int		i;

	i = 0;
	start = malloc(atoi(argv[1]));
	while (i++ < 10)
	{
		if(i == 3)
			tmp = malloc(atoi(argv[1]));
		else
			malloc(atoi(argv[1]));
	}
	dump_mem(start - 128, 64 * 20, 32);

	cursor = start - sizeof(t_metadata);
	while (cursor)
	{
		if (cursor->magic_number != MAGIC_NUMBER_BLOC)
			printf("CURSOR N'EST PAS SUR UN BLOC\n");
		if ((char*)cursor + sizeof(t_metadata) != tmp)
		{
			printf("FREE UN BLOC\n");
			cursor->free = 1;
		}
		cursor = cursor->next;
	}


	realloc(tmp, atoi(argv[1]) + 2);
	dump_mem(start - 128, 64 * 20, 32);
	return 0;
}

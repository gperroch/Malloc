/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 12:03:19 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 12:09:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		dump_mem(void *ptr, int len, int col, char *name)
{
	int		i;
	char	*mem;

	i = 0;
	mem = ptr;
	printf("%6s |----------------------| ", name);
	while (i++ < col)
		printf("%2d ", i);
	printf("\n");
	i = 0;
	while (i < len)
	{
		if (i == 0 || i % col == 0)
			printf("%6d | %20p | ", i, ptr);
		if (mem[i] != 0)
			printf("\033[31m");
		printf("%02hhx ", mem[i]);
		printf("\033[0m");
		ptr++;
		i++;
		if (i == len || i % col == 0)
			printf("\n");
	}
}

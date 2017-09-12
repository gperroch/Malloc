/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 12:03:19 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/12 13:46:58 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		dump_mem(void *ptr, int len, int col)
{
	int		i;
	char	*mem;

	i = 0;
	mem = ptr;
	printf("%6c |----------------------|  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32\n", '-');
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

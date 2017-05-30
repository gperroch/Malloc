/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:28:50 by gperroch          #+#    #+#             */
/*   Updated: 2017/05/16 16:10:58 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define DEBUG(x) write(1, x, ft_strlen(x));

int			main(int argc, char **argv)
{
	int		allocations_tiny;
	int		allocations_small;
	int		allocations_large;
	int		size;
	void	*ptr;

	if (argc < 2)
	{
		printf("Usage: ./a.out number_tiny_allocations number_small_allocations number_large_allocations sleep_time");
		return 0;
	}
	allocations_tiny = atoi(argv[1]);
	allocations_small = atoi(argv[2]);
	allocations_large = atoi(argv[3]);
//	printf("AREA_SMALL = %d, AREA_TINY = %d\n", AREA_SMALL, AREA_TINY);
	while (allocations_tiny--)
	{
		size = rand() % TINY;
		ptr = malloc(size);
//		printf("Allocation TINY  (%5d octets) : %d.\n", size, ptr);
	}

	while (allocations_small--)
	{
		size = rand() % SMALL;
		ptr = malloc(size);
//		printf("Allocation SMALL (%5d octets) : %d.\n", size, ptr);
	}

	while (allocations_large--)
	{
		size = rand() % 99999;
		ptr = malloc(size);
//		printf("Allocation LARGE (%5d octets) : %d.\n", size, ptr);
	}

	sleep(atoi(argv[4]));
	return 0;
}

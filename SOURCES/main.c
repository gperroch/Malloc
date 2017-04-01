/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/04/01 14:06:12 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*ptr;
	void	*ptrtab[10];
	void	*start;
	int		i;
	int		max;

//	i = 0;
	max = 10;
//	printf("sizeof(t_area) = %lu, sizeof(t_block) = %lu\n", sizeof(t_area), sizeof(t_block));
//	ptrtab = (void**)malloc(sizeof(void*) * max);
	printf("ptrtab + (sizeof(void*) * max) = %p\n", ptrtab + (sizeof(void*) * max));

	start = malloc(atoi(argv[1]));
	ft_memset(start, 255, atoi(argv[1]));
	
	ptr = malloc(atoi(argv[1]));
	ft_memset(ptr, 254, atoi(argv[1]));
	ptr = malloc(atoi(argv[1]));
	ft_memset(ptr, 253, atoi(argv[1]));
	ptr = malloc(atoi(argv[1]));
	ft_memset(ptr, 252, atoi(argv[1]));
	ptr = malloc(atoi(argv[1]));
	ft_memset(ptr, 251, atoi(argv[1]));
	dump_mem(start - 64, 64 * 60, 32);
/*
	while (i < max)
	{
		printf("while 1\n");
		ptrtab[i] = malloc(atoi(argv[1]));
		ft_memset(ptrtab[i], 255 - i, atoi(argv[1]));
		dump_mem(start - 64, 64 * 82, 64);
		i++;
	}
	while (i >= 0)
	{
		printf("while 2\n");
		free(ptrtab[i]);
		i++;
	}
	realloc(start, atoi(argv[1]) * 4);	*/
	return 0;
}

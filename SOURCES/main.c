/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/28 11:35:25 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*ptr1;

	printf("sizeof(t_area) = %lu, sizeof(t_block) = %lu\n", sizeof(t_area), sizeof(t_block));
	
	ptr1 = malloc(atoi(argv[1]));
	ft_memset(ptr1, 255, atoi(argv[1]));
	dump_mem(ptr1 - 64, 256);
	ptr1 = malloc(atoi(argv[1]));
	ft_memset(ptr1, 170, atoi(argv[1]));
	dump_mem(ptr1 - 64, 256);
	free(ptr1);
	printf("FREE\n");
	dump_mem(ptr1 - 64, 256);
	ptr1 = malloc(atoi(argv[1]));
	ft_memset(ptr1, 170, atoi(argv[1]));
	dump_mem(ptr1 - 64, 256);
	return 0;
}

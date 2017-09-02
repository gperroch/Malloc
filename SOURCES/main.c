/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/02 18:21:26 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*start;
	void	*tmp;
	int		i;

	i = 0;
	start = malloc(atoi(argv[1]));
	while (++i < 150)
	{
		tmp = malloc(atoi(argv[1]));
		printf("Allocation %3d : %p\n", i + 1, tmp);
	}
	i = 0;
	while (++i < 150)
	{
		tmp = malloc(atoi(argv[1]) * 10);
		printf("Allocation x10 %3d : %p\n", i + 1, tmp);
	}

	dump_mem(start - 64, 64 * 300, 32);
	return 0;
}

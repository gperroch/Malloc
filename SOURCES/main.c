/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/02 15:22:33 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*start;

	start = malloc(atoi(argv[1]));
	ft_memset(start, 255, atoi(argv[1]));
	malloc(atoi(argv[1]));
	//malloc(atoi(argv[1]));
	//malloc(atoi(argv[1]));

	//dump_mem(start - 64, 64 * 30, 32);
	return 0;
}

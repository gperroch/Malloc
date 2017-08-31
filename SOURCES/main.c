/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/08/31 17:43:57 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*start;

	start = malloc(atoi(argv[1]));

	//dump_mem(start - 64, 64 * 30, 32);
	return 0;
}

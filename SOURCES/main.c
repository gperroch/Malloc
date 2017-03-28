/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/22 13:34:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int main(int argc, char **argv)
{
	void *ptr1;
	void *ptr2;
	int i = 0;

	while (i++ < 10)
	{
		ptr1 = malloc(atoi(argv[1]));
		dump_mem(ptr1 - (i * (32 + atoi(argv[1])) + 32), 256);
	}
	return 0;
}

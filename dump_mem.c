/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 12:03:19 by gperroch          #+#    #+#             */
/*   Updated: 2016/05/17 16:50:19 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		dump_mem(void *ptr, int len)
{
	int		i;
	char	*mem;

	i = 0;
	mem = ptr;
	while (i < len)
	{
		if (i == 0 || i % 32 == 0)
			printf("%6d | %20p | ", i, ptr);
		printf("%02hhx ", mem[i]);
		ptr++;
		i++;
		if (i == len || i % 32 == 0)
			printf("\n");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_charge_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:46:30 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/21 09:47:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				test_charge(int isfree)
{
	char		*ptr;
	size_t		size;
	int			limit;

	sub_test_charge_one(10000, 127, isfree, 1);
	sub_test_charge_one(10000, 1023, isfree, 2);
	sub_test_charge_one(10000, 1025, isfree, 3);
	sub_test_charge_two(10000, 1, isfree, 4);
	return (0);
}

void			sub_test_charge_one(int limit, size_t size, int isfree, int nbr)
{
	char		*ptr;

	ptr = NULL;
	printf("\ttest_charge_one %d.\n", nbr);
	while (limit--)
	{
		if (ptr != NULL && isfree)
			free(ptr);
		ptr = malloc(size);
	}
}

void			sub_test_charge_two(int limit, size_t size, int isfree, int nbr)
{
	char		*ptr;

	ptr = NULL;
	printf("\ttest_charge_two %d.\n", nbr);
	while (limit--)
	{
		if (ptr != NULL && isfree)
			free(ptr);
		ptr = malloc(size + limit);
	}
}

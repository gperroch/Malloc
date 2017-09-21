/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_malloc_realloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:43:01 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/21 09:50:01 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				test_malloc_realloc(void)
{
	int			res;
	int			ret;

	res = 0;
	ret = 0;
	res = sub_test_malloc_realloc_one(1, 2);
	ret = res ? res : ret;
	res = sub_test_malloc_realloc_two(1, AREA_SMALL + 1);
	ret = res ? res : ret;
	res = sub_test_malloc_realloc_three(1, AREA_TINY / 2);
	ret = res ? res : ret;
	res = sub_test_malloc_realloc_four(1, AREA_TINY / 2);
	ret = res ? res : ret;
	return (ret);
}

int				sub_test_malloc_realloc_one(size_t first_size, size_t new_size)
{
	void		*ptr;
	void		*ptr2;
	t_metadata	*bloc;

	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	printf("\ttest_malloc_realloc 1.\n");
	ptr = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 != 0x0 || bloc->size_data < new_size)
		return (1);
	return (0);
}

int				sub_test_malloc_realloc_two(size_t first_size, size_t new_size)
{
	void		*ptr;
	void		*ptr2;
	t_metadata	*bloc;

	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	printf("\ttest_malloc_realloc 2.\n");
	ptr = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 == 0x0)
		return (20);
	if (bloc->size_data < new_size)
		return (21);
	return (0);
}

int				sub_test_malloc_realloc_three(size_t first_size,
	size_t new_size)
{
	void		*ptr;
	void		*ptr2;
	t_metadata	*bloc;

	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	printf("\ttest_malloc_realloc 3.\n");
	ptr = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 != 0x0 || bloc->size_data < new_size)
		return (3);
	return (0);
}

int				sub_test_malloc_realloc_four(size_t first_size, size_t new_size)
{
	void		*ptr;
	void		*ptr2;
	t_metadata	*bloc;
	int			i;

	i = 90;
	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	printf("\ttest_malloc_realloc 4.\n");
	ptr = malloc(first_size);
	bloc = ptr - sizeof(t_metadata);
	while (--i)
		ptr2 = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 == 0x0)
		return (40);
	if (bloc->size_data < new_size)
		return (41);
	return (0);
}

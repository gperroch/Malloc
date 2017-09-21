/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 09:43:05 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/21 09:48:58 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				test_malloc(void)
{
	int			res;
	int			ret;

	res = 0;
	ret = 0;
	res = sub_test_malloc_ok(NULL, 0, 1);
	ret = res ? res : ret;
	res = sub_test_malloc_ko(NULL, -1, 2);
	ret = res ? res : ret;
	res = sub_test_malloc_ok(NULL, 32, 3);
	ret = res ? res : ret;
	res = sub_test_malloc_ok(NULL, 2147483647, 4);
	ret = res ? res : ret;
	res = sub_test_malloc_ok(NULL, 2147483648, 5);
	ret = res ? res : ret;
	res = sub_test_malloc_ko(NULL, -2147483648, 6);
	ret = res ? res : ret;
	res = sub_test_malloc_ko(NULL, -2147483649, 7);
	ret = res ? res : ret;
	res = sub_test_malloc_ko(NULL, -32, 8);
	ret = res ? res : ret;
	return (ret);
}

int				sub_test_malloc_ok(void *ptr, long int size, int nbr)
{
	printf("\ttest_malloc %d.\n", nbr);
	ptr = malloc(size);
	if (!ptr)
		return (nbr);
	return (0);
}

int				sub_test_malloc_ko(void *ptr, long int size, int nbr)
{
	printf("\ttest_malloc %d.\n", nbr);
	ptr = malloc(size);
	if (ptr)
		return (nbr);
	return (0);
}

int				test_malloc_free(void)
{
	void		*ptr;
	t_metadata	*bloc;

	ptr = NULL;
	bloc = NULL;
	printf("\ttest_malloc_free 1.\n");
	ptr = malloc(1);
	bloc = ptr - sizeof(t_metadata);
	if (bloc->free)
		return (1);
	free(ptr);
	if (!bloc->free)
		return (2);
	printf("\ttest_malloc_free 2.\n");
	free(ptr);
	if (!bloc->free)
		return (3);
	return (0);
}

int				test_malloc_free_realloc(void)
{
	void		*ptr;
	void		*ptr2;
	size_t		first_size;
	size_t		new_size;

	ptr = NULL;
	ptr2 = NULL;
	first_size = 11;
	new_size = 20;
	printf("\ttest_malloc_free_realloc 1.\n");
	ptr = malloc(first_size);
	free(ptr);
	ptr2 = realloc(ptr, new_size);
	if (ptr - ptr2 == 0x0 && ((t_metadata*)ptr2)->size_total == new_size)
		return (1);
	return (0);
}

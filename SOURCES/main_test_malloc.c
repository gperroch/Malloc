/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/21 10:06:19 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				main(void)
{
	char		*res;
	int			code;

	execute_test(test_charge(1), "test_charge avec free");
	execute_test(test_charge(0), "test_charge sans free");
	execute_test(test_malloc(), "test_malloc");
	execute_test(test_malloc_free(), "test_malloc_free");
	execute_test(test_malloc_realloc(), "test_malloc_realloc");
	execute_test(test_malloc_free_realloc(), "test_malloc_free_realloc");
	execute_test(test_realloc(), "test_realloc");
	execute_test(test_realloc_free(), "test_realloc_free");
	show_alloc_mem();
	return (0);
}

void			execute_test(int code, char *label)
{
	char		*res;

	res = code ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", label, res, code);
}

int				test_realloc(void)
{
	void		*ptr;
	t_metadata	*bloc;

	printf("\ttest_realloc 1.\n");
	bloc = NULL;
	ptr = realloc(NULL, 0);
	bloc = ptr - sizeof(t_metadata);
	if (ptr == NULL)
		return (10);
	if (bloc->size_total != 0)
		return (11);
	printf("\ttest_realloc 2.\n");
	bloc = NULL;
	ptr = realloc(NULL, 10);
	bloc = ptr - sizeof(t_metadata);
	if (ptr == NULL)
		return (20);
	if (bloc->size_total != 10)
		return (21);
	printf("\ttest_realloc 3.\n");
	bloc = NULL;
	ptr = realloc(NULL, -1);
	if (ptr != NULL)
		return (3);
	return (0);
}

int				test_realloc_free(void)
{
	void		*ptr;
	t_metadata	*bloc;

	printf("\ttest_realloc_free 1.\n");
	ptr = realloc(NULL, 0);
	bloc = ptr - sizeof(t_metadata);
	free(ptr);
	if (ptr == NULL)
		return (10);
	if (bloc->size_total != 0 || !bloc->free)
		return (11);
	printf("\ttest_realloc_free 2.\n");
	ptr = realloc(NULL, 10);
	bloc = ptr - sizeof(t_metadata);
	free(ptr);
	if (ptr == NULL)
		return (20);
	if (bloc->size_total != 10 || !bloc->free)
		return (21);
	printf("\ttest_realloc_free 3.\n");
	ptr = realloc(NULL, -1);
	free(ptr);
	if (ptr != NULL)
		return (3);
	return (0);
}

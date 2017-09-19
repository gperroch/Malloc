/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:07:49 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/19 13:02:03 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <limits.h>

#define DEBUG(x) printf("[DEBUG] %s\n", x);
int			test_malloc();
int			test_malloc_free();
int			test_malloc_realloc();
int			test_malloc_free_realloc();
int			test_realloc();
int			test_realloc_free();
int			test_charge(int _free);

int			main()
{
	char	*res;
	int		code;

	printf("sizeof(t_metadata):%zu\n", sizeof(t_metadata));
	printf("AREA_TINY:%lu\nAREA_TINY/4096:%f\nAREA_SMALL:%lu\nAREA_SMALL/4096:%f\n", AREA_TINY, (double)((double)AREA_TINY/4096), AREA_SMALL, (double)((double)AREA_SMALL/4096));

	res = "NULL";
	res = (code = test_charge(1)) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_charge avec free", res, code);

/*	res = "NULL";
	res = (code = test_charge(0)) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_charge sans free", res, code);
*/
	res = "NULL";
	res = (code = test_malloc()) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_malloc", res, code);

	res = "NULL";
	res = (code = test_malloc_free()) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_malloc_free", res, code);

	res = "NULL";
	res = (code = test_malloc_realloc()) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_malloc_realloc", res, code);

	res = "NULL";
	res = (code = test_malloc_free_realloc()) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_malloc_free_realloc", res, code);

	res = "NULL";
	res = (code = test_realloc()) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_realloc", res, code);

	res = "NULL";
	res = (code = test_realloc_free()) ? "FAIL" : "SUCCESS";
	printf("%-30s: %7s (%d)\n", "test_realloc_free", res, code);

	show_alloc_mem();
	printf("AREA_TINY:%lu AREA_SMALL:%lu\n", AREA_TINY, AREA_SMALL);

	return 0;
}

int				test_charge(int _free)
{
	char		*ptr;
	size_t		size;
	int			limit;

	limit = 10000;
	size = 127;

	ptr = NULL;
	while (limit--)
	{
		if (ptr != NULL && _free)
			free(ptr);
		ptr = malloc(size);
	}

	limit = 10000;
	size = 1023;

	ptr = NULL;
	while (limit--)
	{
		if (ptr != NULL && _free)
			free(ptr);
		ptr = malloc(size);
	}

	limit = 10000;
	size = 1025;

	ptr = NULL;
	while (limit--)
	{
		if (ptr != NULL && _free)
			free(ptr);
		ptr = malloc(size);
	}

	limit = 10000;
	size = 1;

	ptr = NULL;
	while (limit--)
	{
		if (ptr != NULL && _free)
			free(ptr);
		ptr = malloc(size + limit);
	}
	return (0);
}

int			test_malloc()
{
	void 		*ptr;
	long int	size;

	ptr = NULL;

	printf("\ttest_malloc 1.\n");
	size = 0;
	ptr = malloc(size);
	if (!ptr)
		return (1);
	ptr = NULL;

	printf("\ttest_malloc 2.\n");
	size = -1;
	ptr = malloc(size);
	if (ptr)
		return (2);
	ptr = NULL;

	printf("\ttest_malloc 3.\n");
	size = 32;
	ptr = malloc(size);
	if (!ptr)
		return (3);
	ptr = NULL;

	printf("\ttest_malloc 4.\n");
	size = 2147483647;
	ptr = malloc(size);
	if (!ptr)
		return (4);
	ptr = NULL;

	printf("\ttest_malloc 5.\n");
	size = 2147483648;
	ptr = malloc(size);
	if (!ptr)
		return (5);
	ptr = NULL;

	printf("\ttest_malloc 6.\n");
	size = -2147483648;
	ptr = malloc(size);
	if (ptr)
		return (6);
	ptr = NULL;

	printf("\ttest_malloc 7.\n");
	size = -2147483649;
	ptr = malloc(size);
	if (ptr)
		return (7);
	ptr = NULL;

	printf("\ttest_malloc 8.\n");
	size = -32;
	ptr = malloc(size);
	if (ptr)
		return (8);
	ptr = NULL;

	return (0);
}

int				test_malloc_free()
{
	void 		*ptr;
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


int			test_malloc_realloc() // Verifier que les donnees sont bien recopiees lors d'un realloc trop grand.
{
	void 		*ptr;
	void 		*ptr2;
	t_metadata	*bloc;
	size_t		first_size;
	size_t		new_size;
	int			i;

	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	first_size = 1;
	new_size = 2;

	printf("\ttest_malloc_realloc 1.\n");
	ptr = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 != 0x0 || bloc->size_data < new_size)
		return (1);

	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	first_size = 1;
	new_size = AREA_SMALL + 1;

	printf("\ttest_malloc_realloc 2.\n"); // Ce test doit prendre en compte le depassement de zone.
	ptr = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 == 0x0)
		return (20);
	if (bloc->size_data < new_size)
		return (21);

	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	first_size = 1;
	new_size = AREA_TINY / 2;

	printf("\ttest_malloc_realloc 3.\n"); // Ce test demande une reallocation de taille suffisante pour entrer dans une AREA_TINY, mais l'area ne contient pas encore assez de bloc pour avoir une place suffisante.
	ptr = malloc(first_size);
	ptr2 = realloc(ptr, new_size);
	bloc = ptr2 - sizeof(t_metadata);
	if (ptr - ptr2 != 0x0 || bloc->size_data < new_size)
		return (3);

	i = 90;
	ptr = NULL;
	ptr2 = NULL;
	bloc = NULL;
	first_size = 1;
	new_size = AREA_TINY / 2;

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

int			test_malloc_free_realloc()
{
	void 	*ptr;
	void 	*ptr2;
	size_t 	first_size;
	size_t 	new_size;

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


int				test_realloc()
{
	void 		*ptr;
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

	return(0);
}

int			test_realloc_free()
{
	void 		*ptr;
	t_metadata	*bloc;

	printf("\ttest_realloc_free 1.\n");
	bloc = NULL;
	ptr = realloc(NULL, 0);
	bloc = ptr - sizeof(t_metadata);
	free(ptr);
	if (ptr == NULL)
		return (10);
	if (bloc->size_total != 0)
		return (11);
	if (!bloc->free)
		return (12);

	printf("\ttest_realloc_free 2.\n");
	bloc = NULL;
	ptr = realloc(NULL, 10);
	bloc = ptr - sizeof(t_metadata);
	free(ptr);
	if (ptr == NULL)
		return (20);
	if (bloc->size_total != 10)
		return (21);
	if (!bloc->free)
		return (22);

	printf("\ttest_realloc_free 3.\n");
	bloc = NULL;
	ptr = realloc(NULL, -1);
	free(ptr);
	if (ptr != NULL)
		return (3);

	return (0);
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int			main(int argc, char **argv)
{
	char	*ptr;
	long int		size;
	size_t	sizet;
	int		choice;

	choice = atoi(argv[1]);
	ptr = NULL;
	if (choice == 0)
	{
		size = 0;
		ptr = malloc(size);
		printf("size:%ld => ptr:%p\n", size, ptr);
	}
	if (choice == 1)
	{
		size = -32;
		ptr = malloc(size);
		printf("size:%ld => ptr:%p\n", size, ptr);
	}
	if (choice == 2)
	{
		size = 2147483647;
		ptr = malloc(size);
		printf("size:%ld => ptr:%p\n", size, ptr);
	}
	if (choice == 3)
	{
		size = 2147483648;
		ptr = malloc(size);
		printf("size:%ld => ptr:%p\n", size, ptr);
		printf("2power%lu:%f\n", sizeof(size_t), pow(2, 8 * sizeof(size_t)));
	}
	if (choice == 4)
	{
		size = -2147483648;
		ptr = malloc(size);
		printf("size:%ld => ptr:%p\n", size, ptr);
	}
	if (choice == 5)
	{
		size = -2147483649;
		ptr = malloc(size);
		printf("size:%ld => ptr:%p\n", size, ptr);
	}
	if (choice == 6)
	{
		sizet = 18446744073709551615;
		ptr = malloc(sizet);
		printf("sizet:%ld => ptr:%p\n", sizet, ptr);
	}
	return (0);
}

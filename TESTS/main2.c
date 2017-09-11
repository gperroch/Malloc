#include <stdlib.h>
#include <stdio.h>

int			main(int argc, char **argv)
{
	char	*ptr;
	int		size;

	ptr = NULL;
//	size = 2147483648;
	size = 10;
//	ptr = malloc((size_t)size);
	ptr = malloc((size_t)size);
	printf("ptr malloc(%d) 1 : %p\n", size, ptr);
	free(ptr);
	printf("ptr freed\n");
	realloc(ptr, 15);
	printf("ptr realloue\n");

	return (0);
}

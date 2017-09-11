#include <stdlib.h>
#include <stdio.h>

int			main(int argc, char **argv)
{
	char	*ptr;

	ptr = malloc(20);
	printf("ptr malloc(14) 1 : %p\n", ptr);
	ptr = realloc(ptr, 18);
	printf("ptr realloc: %p\n", ptr);

	return (0);
}

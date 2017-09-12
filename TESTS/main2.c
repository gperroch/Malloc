#include <stdlib.h>
#include <stdio.h>

int			main(int argc, char **argv)
{
	char	*ptr;
	int		size;
	size_t	sizet;

	ptr = malloc(1);
	size = 10;
	sizet = atoi(argv[1]);

	printf("ptr = %p\n", ptr);
	ptr = realloc(ptr, atoi(argv[1]));
	printf("ptr = %p\n", ptr);
	printf("argv[1] = %d/ sizet = %zu/ (int)sizet = %d\n", atoi(argv[1]), sizet, (int)sizet);
	return (0);
}

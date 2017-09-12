#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*ptr;
	int		i;

	i = atoi(argv[1]);
	ptr = malloc(100000);
	ft_memset(ptr, 60, 100000);
	dump_mem((char*)ptr - (2 * sizeof(t_metadata)), 32 * 30, 32);
	while (i-- > 0)
	{
		write(1, ".", 1);
		sleep(1);
		if (i == 15)
			free(ptr);
	}
	return (0);
}

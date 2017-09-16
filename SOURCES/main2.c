#include "malloc.h"

#define DEBUG(x) printf("[DEBUG] %s\n", x);

int			main(int argc, char **argv)
{
	void	*ptr;
	int		i;

	i = atoi(argv[1]);
	ptr = malloc(10);
	ft_memset(ptr, 60, 10);
	dump_mem((char*)ptr - (2 * sizeof(t_metadata)), 32 * 30, 32, "main2");
	while (i-- > 0)
	{
		write(1, ".", 1);
		sleep(1);
		if (i == 15)
		{
			write(1, "*", 1);
			free(ptr);
		}
	}
	return (0);
}

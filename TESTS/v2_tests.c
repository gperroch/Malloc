#include "malloc.h"

int 	main()
{

	return (0);
}

void			assert(bool result, char *name)
{
	if (!result)
		printf("%s : \033[31mFAILURE\033[0m\n", name);
	else
		printf("%s : \033[32mSUCCESS\033[0m\n", name);
}

bool			ft_mapping_test()
{
	void		*ptr;
	size_t		size;
	t_area_v2	*area;

	area = ft_mapping(ptr, size);
}

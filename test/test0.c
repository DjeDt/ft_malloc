#include "malloc.h"
int	main()
{
	void *ptr = malloc(16);
	free(ptr);
	return (0);
}

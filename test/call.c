#include "malloc.h"

int main(void)
{
	void *ret = calloc(2880, 5);
//	void *ret = malloc(16000);
	free(ret);
	return (0);
}

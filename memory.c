#include "shell.h"

/**
 * bfree - It lets a ptr be free in an add function
 * @ptr: Free ptr add function
 * Return: if freed return 1 and 0 if not
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


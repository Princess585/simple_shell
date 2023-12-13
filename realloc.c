#include "shell.h"

/**
 **_memset - It sets the file memory in the function
 *@s: The mem setting ptr of functs
 *@b: The byte setting ptr of the funct
 *@n: The numb of bytes in the mem
 *Return: The function's memory ptr
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int e;

	for (e = 0; e < n; e++)
		s[e] = b;
	return (s);
}

/**
 * ffree - The memory is freed by a doule string
 * @pp: Two or double strings in a funct
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - This reallocates a set of memory functions
 * @ptr: The ptr to the realloc sttings of a mem
 * @old_size: The old version size of byte
 * @new_size: The new version size of byte
 * Return: The ptr to the block byte sizes
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

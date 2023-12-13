#include "shell.h"

/**
 * _strlen - The str length is to be returned fo this funct sake
 * @s: The str length needed to evaluate
 * Return: The str length of a funct
 */
int _strlen(char *s)
{
	int e = 0;

	if (!s)
		return (0);

	while (*s++)
		e++;
	return (e);
}

/**
 * _strcmp - The string comand to look for
 * @s1: The str to begin with
 * @s2: The str to end with
 * Return: neg(-) if s1 < s2, pos(+) if s1 > s2, zero(0) if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Finds out the needle starts with haystack in this function
 * @haystack: Grass to search to for needle
 * @needle: The needle to search
 * Return: NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - The strng to conc in this funct
 * @dest: The str buf destination
 * @src: The sourse str buf dest
 * Return: Ptr to buf dest in this function
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}


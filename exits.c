#include "shell.h"

/**
 **_strncpy - This function copies a str to be measured
 *@dest: Copied str destination to  it's location
 *@src: Source of the str copied to it's dest
 *@n: Characters copied numb
 *Return: A str that is copied
 */
char *_strncpy(char *dest, char *src, int n)
{
	int e, f;
	char *s = dest;

	e = 0;
	while (src[e] != '\0' && e < n - 1)
	{
		dest[e] = src[e];
		e++;
	}
	if (e < n)
	{
		f = e;
		while (f < n)
		{
			dest[f] = '\0';
			f++;
		}
	}
	return (s);
}

/**
 **_strncat - This funct conca two strs
 *@dest: First str on the destination line
 *@src: Sec str on the line
 *@n: Numb and amount a byte is needed
 *Return: Str just got concatenated
 */
char *_strncat(char *dest, char *src, int n)
{
	int e, f;
	char *s = dest;

	e = 0;
	f = 0;
	while (dest[e] != '\0')
		e++;
	while (src[f] != '\0' && f < n)
	{
		dest[e] = src[f];
		e++;
		f++;
	}
	if (f < n)
		dest[e] = '\0';
	return (s);
}

/**
 **_strchr - Str character location in a function
 *@s: The parsed current str
 *@c: We look at this char in this funct
 *Return: ptr to the char (s)
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

#include "shell.h"

/**
 * _strcpy - This function copies the str
 * @dest: The copies destination to follow
 * @src: The copies source of str
 * Return: The dest ptr
 */
char *_strcpy(char *dest, char *src)
{
	int e = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[e])
	{
		dest[e] = src[e];
		e++;
	}
	dest[e] = 0;
	return (dest);
}

/**
 * _strdup - The duplicates or similarities of this str funct
 * @str: The similar str
 * Return: The ptr to thr duplicate str
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - This prints a function to stdout
 *@str: The str of the funct
 * Return: Void
 */
void _puts(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_putchar(str[e]);
		e++;
	}
}

/**
 * _putchar - It writes the chars to stdout
 * @c: The char c to write
 * Return: On success 1 and returns -1 on error
 */
int _putchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}


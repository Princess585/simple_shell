#include "shell.h"

/**
 *_eputs - It prints an input in a str func
 * @str: Str printed to be evaluated
 * Return: Nothing
 */
void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - The char c is written into stderr
 * @c: Print the characters in this manner
 * Return: 1 if on success and -1 on error
 */
int _eputchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putfd - The chars c is written on filedescription
 * @c: Chars c to print to the function
 * @fd: The written filedescriptor in this code
 * Return: 1 on success and -1 on error and failure
 */
int _putfd(char c, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 *_putsfd - Function prints the input str
 * @str: Str printout
 * @fd: The written filedescriptor of a script
 * Return: Num of chars of a script
 */
int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}

#include "shell.h"

/**
 * _erratoi - The function to merge strs and int into one
 * @s: String that was merged with an integer
 * Return: 0 when number is absent and -1 if error occurs
 */
int _erratoi(char *s)
{
	int e = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main ret 255? */
	for (e = 0;  s[e] != '\0'; e++)
	{
		if (s[e] >= '0' && s[e] <= '9')
		{
			result *= 10;
			result += (s[e] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - This func prints error messages
 * @info: The structure of a potential par that is used
 * @estr: An error string type
 * Return: 0 if numbs do not exist and -1 if error occurs in th num
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - This funct prints decimal int numbers
 * @input: Input of thr printed num
 * @fd: The written filedescriptor to print
 * Return: Chars numb
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int e, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (e = 1000000000; e > 1; e /= 10)
	{
		if (_abs_ / e)
		{
			__putchar('0' + current / e);
			count++;
		}
		current %= e;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Clones funcs and numbs
 * @num: The number to be cloned in a func
 * @base: The base of a func
 * @flags: Flags of args numbs
 * Return: A str
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - This removes the first comment of a funct
 * @buf: The buffer add to change
 * Return: 0 all the time
 */
void remove_comments(char *buf)
{
	int e;

	for (e = 0; buf[e] != '\0'; e++)
		if (buf[e] == '#' && (!e || buf[e - 1] == ' '))
		{
			buf[e] = '\0';
			break;
		}
}

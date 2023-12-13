#include "shell.h"

/**
 * interactive - The func that ret real in shell
 * @info: Add structed
 * Return: 0 if it fails and 1 if int pass
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - The chars deli of a function
 * @c: checked characters
 * @delim: Deli string of a function
 * Return: 0 is false and 1 is when it is true
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - The alphabetic chars in a func is to be checked
 *@c: Input charact in a func
 *Return: 1 if c is alpha and 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - The function that convs to an integer
 *@s: String to conv in a given func
 *Return: The nums must be convereted and 0 is returned
 */

int _atoi(char *s)
{
	int e, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (e = 0;  s[e] != '\0' && flag != 2; e++)
	{
		if (s[e] == '-')
			sign *= -1;

		if (s[e] >= '0' && s[e] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[e] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


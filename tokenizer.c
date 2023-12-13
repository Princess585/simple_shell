#include "shell.h"

/**
 * **strtow - The strings of a splited delimeter found in the func
 * @str: The str to stdin in this function
 * @d: The deli str that are splited
 * Return: On success ptr and NULL on failure or on error
 */

char **strtow(char *str, char *d)
{
	int e, f, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (e = 0; str[e] != '\0'; e++)
		if (!is_delim(str[e], d) && (is_delim(str[e + 1], d) || !str[e + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (e = 0, f = 0; f < numwords; f++)
	{
		while (is_delim(str[e], d))
			e++;
		k = 0;
		while (!is_delim(str[e + k], d) && str[e + k])
			k++;
		s[f] = malloc((k + 1) * sizeof(char));
		if (!s[f])
		{
			for (k = 0; k < f; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[f][m] = str[e++];
		s[f][m] = 0;
	}
	s[f] = NULL;
	return (s);
}

/**
 * **strtow2 - The str is splited into two ways in the function
 * @str: The str to stdin in the funct
 * @d: The delim of a function
 * Return: On success a ptr and NULL on error or failure
 */
char **strtow2(char *str, char d)
{
	int e, f, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != d && str[e + 1] == d) ||
		    (str[e] != d && !str[e + 1]) || str[e + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (e = 0, f = 0; f < numwords; f++)
	{
		while (str[e] == d && str[e] != d)
			e++;
		k = 0;
		while (str[e + k] != d && str[e + k] && str[e + k] != d)
			k++;
		s[f] = malloc((k + 1) * sizeof(char));
		if (!s[f])
		{
			for (k = 0; k < f; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[f][m] = str[e++];
		s[f][m] = 0;
	}
	s[f] = NULL;
	return (s);
}


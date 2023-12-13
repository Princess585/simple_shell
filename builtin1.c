#include "shell.h"

/**
 * _myhistory - History list, command line are proceded in this funct
 * @info: The structure of potential line args in a funct str
 *  Return: 0 all the time
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets an alias in a str function
 * @info: par structure information
 * @str: The alias string that is calculated
 * Return: 0 for failure and 1 for succeeding
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Str and alias and merged together
 * @info: par structure of a func
 * @str: The alias str to be measured
 * Return: 0 for fail and 1 for success
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - The func to print the alias of a code
 * @node: The node of the same alias
 * Return: 0 if fails and 1 if it succeeds
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - The alias that is mimiced in a function
 * @info: The structure of potential line of args is measured
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int e = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (e = 1; info->argv[e]; e++)
	{
		p = _strchr(info->argv[e], '=');
		if (p)
			set_alias(info, info->argv[e]);
		else
			print_alias(node_starts_with(info->alias, info->argv[e], '='));
	}

	return (0);
}

#include "shell.h"

/**
 * list_len - It lists the length og thi function
 * @h: Header to the beginning of a node
 * Return: Listed size in a funct
 */
size_t list_len(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * list_to_strings - Lists the number of string in a funct
 * @head: Header ptr to the node val
 * Return: The size of str arr
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t e = list_len(head), f;
	char **strs;
	char *str;

	if (!head || !e)
		return (NULL);
	strs = malloc(sizeof(char *) * (e + 1));
	if (!strs)
		return (NULL);
	for (e = 0; node; node = node->next, e++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (f = 0; f < e; f++)
				free(strs[f]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[e] = str;
	}
	strs[e] = NULL;
	return (strs);
}


/**
 * print_list - This prints the listed values of a funct
 * @h: Header ptr of a funct
 * Return: The listed size value funct
 */
size_t print_list(const list_t *h)
{
	size_t e = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		e++;
	}
	return (e);
}

/**
 * node_starts_with - The starting node in a str function
 * @node: Header ptr of a funct
 * @prefix: The head of a str sentence
 * @c: The characters of a c node
 * Return: NULL or a node
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Will get the index node of a function
 * @head: Header ptr to a node of a funct
 * @node: Header ptr to a node function
 * Return: The node size of a function
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t e = 0;

	while (head)
	{
		if (head == node)
			return (e);
		head = head->next;
		e++;
	}
	return (-1);
}


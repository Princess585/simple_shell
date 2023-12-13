#include "shell.h"

/**
 * is_chain - This checks if the chain is a delimeter in this funct
 * @info: The struct buf funct info
 * @buf: The buffer of the funct char
 * @p: The IP address of the function buffer
 * Return: 1 on schain success and 0 on failure
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks The first and last chain function
 * @info: The buffer struct info value
 * @buf: The chain buffer of chars
 * @p: The IP address of a struct info
 * @i: The position to start the function info
 * @len: The length of the chain buffer
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Ith replaces the alias in the deli funct
 * @info: The struct potential info of a funct
 * Return: 1 if replaces and 0 if it does not
 */
int replace_alias(info_t *info)
{
	int e;
	list_t *node;
	char *p;

	for (e = 0; e < 10; e++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - It replaces the variables in a function struct
 * @info: The structure of a deli char funct
 * Return: 1 if it replaces and 0 if it does not
 */
int replace_vars(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[e][1], '=');
		if (node)
		{
			replace_string(&(info->argv[e]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[e], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - It Replaces a str in a struct funct
 * @old: The old str IP add
 * @new: The new IP add
 * Return: 1 if it replaces and 0 if it does not
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


#include "shell.h"

/**
 * get_environ - This funct gets the environment struct or char
 * @info: The struct of args values and chars of a funct
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - The unset env is removed from a var in a funct
 * @info: The struct of args values and shars of a function
 * @var: The var str value
 * Return: 1 if del and 0 if not del
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t e = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), e);
			e = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		e++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Funct to equalize vars and str chars in an environ
 * @info: The structure of args values and strs of a char in a func
 * @var: The var of even str and chars of a value
 * @value: The val of even str and chars
 *  Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


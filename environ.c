#include "shell.h"

/**
 * _myenv - Prints the curr env in a func
 * @info: The structure containing args and potential functions
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Function that gets the env value in a project
 * @info: The struct containing args and potential functions
 * @name: The environment value of a funct
 * Return: Value of a func
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - To initialize the environment set value
 * @info: The struct tha contains the args value and potential func
 *  Return: 0 all the time
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect numb of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - It removes the env of a function
 * @info: The struct that contains the args val and potential func
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int e;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (e = 1; e <= info->argc; e++)
		_unsetenv(info, info->argv[e]);

	return (0);
}

/**
 * populate_env_list - It populates the list of env functions
 * @info: The struct that comprise the args val and potential func
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t e;

	for (e = 0; environ[e]; e++)
		add_node_end(&node, environ[e], 0);
	info->env = node;
	return (0);
}


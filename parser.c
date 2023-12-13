#include "shell.h"

/**
 * is_cmd - Is the file a command or not in a function
 * @info: The struct value info of a func
 * @path: The node path to a command func
 * Return: 1 if true and success, and 0 if not
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - The characters that are duplicates or the same
 * @pathstr: The path of a string in a funct
 * @start: The start index of a function
 * @stop: The stopped index of a function
 * Return: Ptr to buf of a char
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int e = 0, k = 0;

	for (k = 0, e = start; e < stop; e++)
		if (pathstr[e] != ':')
			buf[k++] = pathstr[e];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - This funct finds the path command to use
 * @info: The info path to find in a funct
 * @pathstr: The string path to follow
 * @cmd: The command line to follow in the finction
 * Return: The correct path or the NULL funct
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int e = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[e] || pathstr[e] == ':')
		{
			path = dup_chars(pathstr, curr_pos, e);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[e])
				break;
			curr_pos = e;
		}
		e++;
	}
	return (NULL);
}


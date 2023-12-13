#include "shell.h"

/**
 * get_history_file - The hist file that is needed for this funct
 * @info: The par of the struct  in the function
 * Return: Str in the allocated funct
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Funct that writes a hist to stdin
 * @info: The struct parameter info of a funct
 * Return: -1 if error and 1 on success
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - This funct will read the hist in a file
 * @info: The info of a struct paramete in a file
 * Return: Counting the his is success and if not is error
 */
int read_history(info_t *info)
{
	int e, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (e = 0; e < fsize; e++)
		if (buf[e] == '\n')
		{
			buf[e] = 0;
			build_history_list(info, buf + last, linecount++);
			last = e + 1;
		}
	if (last != e)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - A histcount of a list built in a funct
 * @info: The struct of parameter value of an info
 * @buf: The buf value
 * @linecount: The line counted in the hist
 * Return: 0 all the time
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - The changed hist liked num must be renumbered
 * @info: The info struct of vars and chars of an arg funct
 * Return: Histcount numbers
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int e = 0;

	while (node)
	{
		node->num = e++;
		node = node->next;
	}
	return (info->histcount = e);
}


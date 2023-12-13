#include "shell.h"

/**
 * input_buf - The buf that is used to stdin in a function
 * @info: The par struct of a funct
 * @buf: The buf add of a str funct
 * @len: The variable of a str character of a funct
 * Return: The bytes that were read at that time
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buf, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Subracts an old and new line in a funct
 * @info: The structure of par function of a var
 * Return: The bytes that were read at that time
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buf */
	static size_t e, f, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buf */
	{
		f = e; /* init new iterator to cur buf position */
		p = buf + e; /* get ptr for return */

		check_chain(info, buf, &f, e, len);
		while (f < len) /* iterate to semicolon(;) or end */
		{
			if (is_chain(info, buf, &f))
				break;
			f++;
		}

		e = f + 1; /* increment past nulled ';'' */
		if (e >= len) /* reached end of buffer? */
		{
			e = len = 0; /* reset position and len */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back ptr to current command position */
		return (_strlen(p)); /* ret len of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buf from _getline() */
	return (r); /* return len of buf from _getline() */
}

/**
 * read_buf - Thia reads the buf and makes sure it is fine
 * @info: The struct of a par add function
 * @buf: The buffer info of a var funct
 * @i: The buf size
 * Return: The return r valure
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - It gets the next line of a function
 * @info: The par structure of a str funtion
 * @ptr: Pointer to address or NULL function
 * @length: The size of allocated length function
 * Return: The s function
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - The control button is blocked in this funct
 * @sig_num: The signal numb to look out for
 * Return: Void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


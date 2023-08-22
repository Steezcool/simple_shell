#include "shell.h"
/**
 * read_buf - This function Reads a buffer
 * @info: Parameter structure
 * @buf: Buffer to read into
 * @i: Size of the buffer
 * Return: The value r
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
 * get_input - This function Reads a line excluding the newline character
 * @info: Parameter structure
 * Return: The number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;
	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* There are remaining commands in the chain buffer */
	{
		j = i; /* Initialize a new iterator to the current buffer position. */
		p = buf + i; /* Obtain a pointer for returning. */
		check_chain(info, buf, &j, i, len);
		while (j < len) /* Loop until a semicolon or the end is reached */
		{
		if (is_chain(info, buf, &j))
		break;
		j++;
		}
		i = j + 1; /* Increment beyond the nullified characters ';'' */
		if (i >= len) /* end of buffer has been reached */
		{
		i = len = 0; /* Reset both the position and the length */
		info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /* Return the pointer to the current command's position. */
		return (_strlen(p)); /* returns the length of the current command */
	}
	*buf_p = buf; /* If not a chain, pass back buffer from _getline() */
	return (r); /* Return length of buffer from _getline() */
}
/**
 * input_buf - Buffers chained commands
 * @info: Parameter structure
 * @buf: Address of the buffer
 * @len: Address of the length variable
 * Return: The number of bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;
	if (!*len) /* If there is nothing remaining in the buffer, fill it */
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
 * _getline - Retrieves the next line of input from STDIN
 * @info: Parameter structure
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 * Return: The obtained string 's'
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
	return (p ? free(p), -1 : -1)
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
 * sigintHandler - Blocks Ctrl-C signal
 * @sig_num: The signal number
 * Return: Void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

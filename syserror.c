#include "shell.h"
/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: if successful 1.
 * if has error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _eputs - Displays the provided string
 * @str: The string to be shown
 * Return: None
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
	return;
	while (str[i] != '\0')
	{
	_eputchar(str[i]);
	i++;
	}
}
/**
 * _putsfd - Writes an input string to a specified file descriptor
 * @str: The string to be written
 * @fd: The file descriptor to write to
 * Return: The number of characters written
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
	return (0);
	while (*str)
	{
	i += _putfd(*str++, fd);
	}
	return (i);
}
/**
 * _eputchar - Writes the character 'c' to the standard error stream (stderr)
 * @c: The character to be printed
 * Return: if successful, returns 1.
 * if has error, returns -1 and sets errno appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
	write(2, buf, i);
	i = 0;
	}
	if (c != BUF_FLUSH)
	buf[i++] = c;
	return (1);
}

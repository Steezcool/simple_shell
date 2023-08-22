#include "shell.h"
/**
 * interactive - this funtion responds with true if shell is in the interactive mode
 * @info: this shows the struct address
 * Return: 1 if shell is in interactive mode, and 0 if not interactive
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * _isalpha - this function checks alphabet characters
 * @c: inputed character
 * Return: 1 if c is an alphabet character, and 0 if not 
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}
/**
 * _atoi - this funtion to convert strings to integers
 * @s: this represents a string that must be converted
 * Return: 0 if theres no numbers in the string, otherwise show converted number
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;
	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
	if (s[i] == '-')
	sign *= -1;
	if (s[i] >= '0' && s[i] <= '9')
	{
	flag = 1;
	result *= 10;
	result += (s[i] - '0');
	}
	else if (flag == 1)
	flag = 2;
	}
	if (sign == -1)
	output = -result;
	else
	output = result;
	return (output);
}
/**
 * is_delim - This funtion checks for characters that are delimeter
 * @c: the checked character
 * @delim: delimeter string
 * Return: 1 if delimeter is true, and 0 if delimeter is false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	if (*delim++ == c)
	return (1);
	return (0);
}



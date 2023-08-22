#include "shell.h"
/**
 * _strcat - this function integrates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: a pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;
	while (*dest)
	dest++;
	while (*src)
	*dest++ = *src++;
	*dest = *src;
	return (ret);
}
/**
 * _strlen - Calculates the length of a string
 * @s: The string whose length to calculate
 * Return: The integer length of the string
 */
int _strlen(char *s)
{
	int i = 0;
	if (!s)
	return (0);
	while (*s++)
	i++;
	return (i);
}
/**
 * starts_with - Checks if a string starts with a given substring
 * @haystack: The string to search
 * @needle: The substring to find
 * Return: Address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	if (*needle++ != *haystack++)
	return (NULL);
	return ((char *)haystack);
}
/**
 * _strcmp - Compares two strings lexicographically
 * @s1: The first string to compare
 * @s2: The second string to compare
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
	if (*s1 != *s2)
	return (*s1 - *s2);
	s1++;
	s2++;
	}
	if (*s1 == *s2)
	return (0);
	else
	return (*s1 < *s2 ? -1 : 1);
}





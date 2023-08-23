#include "shell.h"
/**
 * populate_env_list - Fills an environment linked list
 * @info: A structure holding possible arguments
 * Return: Always returns 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
/**
 * _getenv - Retrieves the value of an environment variable
 * @info: A structure holding possible arguments
 * @name: The name of the environment variable
 * Return: The value of the environment variable
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
 * _myenv - Displays the current environment variables
 * @info: A structure holding possible arguments
 * Return: Always returns 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _mysetenv - Initializes or modifies an existing one
 * @info: A structure holding possible arguments,
 * Return: Always returns 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
	_eputs("Incorrect number of arguments\n");
	return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}
/**
 * _myunsetenv - Deletes an environment variable
 * @info: A structure holding possible arguments
 * Return: Always returns 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
	_eputs("Too few arguments.\n");
	return (1);
	}
	for (i = 1; i <= info->argc; i++)
	_unsetenv(info, info->argv[i]);
	return (0);
}



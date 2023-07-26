#include "main.h"

/**
 * _setenv - set variable
 * @name: variable name
 * @value: the value that the name will hold
 * @overwrite: whether to replace existing
 * Return: 0 if success else -1
 */
int _setenv(char *name, char *value, int overwrite)
{

	int  result;
	char *variable, *existing;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
	{
		perror("Invalid variable name.\n");
		return (-1);
	}

	if (!overwrite)
	{
		/* Check if the environment variable already exists */
		existing = _getenv(name);
		if (existing != NULL)
			return (0);
	}

	variable = _strncat(_strncat(name, "="), value);


	/* Add the environment variable to the environment */
	result = putenv(variable);
	if (result != 0)
	{
		perror(" Failed to set the environment variable.\n");
		return (-1);
	}
	return (0);
}

/**
 * _unsetenv - Remove variable from the list
 * @name: the variable name
 * Return: 0
 */
int _unsetenv(char *name)
{
	putenv(name);

	return (0);
}


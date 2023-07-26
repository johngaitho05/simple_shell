# include "main.h"

/**
 * _issub - checks whether s1 is a substring of s2
 * @s1: a string
 * @s2: a longer string
 * Return: 0 if it is a substring else -1
 */
int _issub(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '\0')
		return (0);

	return (-1);
}

/**
 * _getenv - retrieves the value pointed to by a a variable name
 * @varname: the variable name
 * Return: the corresponding value or NULL
 */
char *_getenv(char *varname)
{
	char *separator, *variable;
	int i = 0;

	if (varname == NULL || _strlen(varname) == 0)
		return (NULL);

	variable = environ[i];
	while (variable)
	{
		separator = _strchr(variable, '=');
		if (separator)
		{
			if (_issub(varname, variable) == 0)
				return (separator + 1);
		}
		i++;
		variable = environ[i];
	}
	return (NULL);
}

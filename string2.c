#include "main.h"


/**
 * _arraylen - computes the size of a null-terminated array
 * @array: a nul-terminated array of strings
 * Return: number of elements in the array
 */
int _arraylen(char **array)
{
	int count  = 0;

	while (array[count] != NULL)
		count++;
	return (count);
}


/**
 * _strip - remove specific characters at the beginning and end of string
 * @str: the string to strip
 * @tokens: characters to remove
 * Return: void (modifies input string in place)
 */
char  *_strip(char *str, char *tokens)
{
	int length = _strlen(str), i = 0;

	if (!tokens)
		tokens = " \n\r";

	if (length > 0)
	{
		/* Remove leading spaces **/
		while (i < length && strchr(tokens, str[i]))
			i++;
		memmove(str, str + i, length - i + 1);

		/* Remove trailing spaces */
		while (length > 0 && strchr(tokens, str[length - 1]))
		{
			str[length - 1] = '\0';
			length--;
		}
	}

	return (str);
}

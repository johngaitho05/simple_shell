#include "main.h"

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: the duplicate string
 */
char *_strdup(char *str)
{

	size_t len = _strlen(str);
	char *new_str;

	if (str == NULL)
	{
		return (NULL);
	}
	new_str = (char *)malloc((len + 1) * sizeof(char));

	if (new_str != NULL)
	{
		_strcpy(new_str, str);
	}

	return (new_str);
}

/**
 * _memmove -copies a block of memory
 * @dest: where to copy to
 * @src: where to copy from
 * @n: number of bytes to copy
 * Return: pointer to the copied memory block
 */
void *_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;
	size_t i;

	if (d < s)
	{
		for (i = 0; i < n; i++)
		{
			d[i] = s[i];
		}
	}
	else if (d > s)
	{
		for (i = n; i > 0; i--)
		{
			d[i - 1] = s[i - 1];
		}
	}

	return (dest);
}

/**
 * _strchr - check whether a character exists
 * @s: the string to search the char in
 * @c: the char to search
 * Return: 1 if it exists else 0
 */
int _strchr(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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
		while (i < length && _strchr(tokens, str[i]))
			i++;
		_memmove(str, str + i, length - i + 1);

		/* Remove trailing spaces */
		while (length > 0 && _strchr(tokens, str[length - 1]))
		{
			str[length - 1] = '\0';
			length--;
		}
	}

	return (str);
}


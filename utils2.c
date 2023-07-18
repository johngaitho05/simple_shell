#include "main.h"

/**
 * _strtok_helper - computes the next substring
 * given the buffer string and the delimiters
 * @s: the string from which to extract a substring
 * @delim: tokens on which to split the input string
 * Return: the next substring matching the split criteria
 */
char *_strtok_helper(char *s, const char *delim)
{
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;

	if (s == NULL)
		s = last;
	if (s  == NULL)
		return (NULL);
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;)
		if (c == sc)
			goto cont;

	if (c == 0)
	{
		last = NULL;
		return (NULL);
	}
	tok = s - 1;
	for (;;)
	{
		c = *s++;
		spanp = (char *)delim;
		do {
			sc = *spanp++;
			if (sc == c)
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
}

/**
 * _strtok - splits a string in to substrings based on the
 * specified delimiters and stores the result in an array
 * @buffer: the string to split
 * @delim: the delimiters (a string)
 * Return: an array of substrings
 */
char **_strtok(char *buffer, const char *delim)
{
	int count = 0, size = 100, bytes_count = 0, required, length;
	char **result = malloc(sizeof(char) * 100);
	char **resized, *token;

	if (result == NULL)
		panic("Memory allocation failed");

	token = _strtok_helper(buffer, delim);
	while (token != NULL)
	{
		_strip(token); /* remove trailing spaces */
		length = _strlen(token);
		required = bytes_count + length;
		if (required > size)
		{
			resized = realloc(result, sizeof(char) * (size + 100));
			if (resized == NULL)
				panic("Memory allocation failed");
			result = resized;
			size += 100;
		}
		result[count] = token;
		bytes_count += length;
		count++;
		token = _strtok_helper(NULL, delim);
	}
	return (result);
}
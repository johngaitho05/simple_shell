#include "main.h"

#define BUFFER_SIZE 128

/**
 * _atoi- convert string to int
 * @str: the string to convert
 * Return: the converted number
 */
int _atoi(char *str)
{
	int num = 0, i;

	for (i = 0; str[i] != '\0'; i++)
	{
		num = num * 10 + (str[i] - 48);
	}

	return (num);
}

/**
 * panic - prints an error message and exist the process
 * @msg: the error message to print
 * Return: 1 to indicate fail
 */
int panic(char *msg)
{
	/* TODO: Format errors correctly */
	_puts(msg, 1);
	exit(1);
}

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
	int count = 0, size = BUFFER_SIZE, bytes_count = 0, required, length;
	char **result = malloc(sizeof(char) * BUFFER_SIZE);
	char **resized, *token;

	if (result == NULL)
		panic("Memory allocation failed");

	token = _strtok_helper(buffer, delim);
	while (token != NULL)
	{
		token = _strip(token, " \n\r"); /* remove trailing spaces */
        if (token[0] == '$')
			/* Replace with the actual value */
			token = getenv(_strip(token, "$"));
		length = _strlen(token);
		required = bytes_count + length;
		if (required > size)
		{
			resized = realloc(result, sizeof(char) * (size + BUFFER_SIZE));
			if (resized == NULL)
				panic("Memory allocation failed");
			result = resized;
			size += BUFFER_SIZE;
		}
		result[count] = token;
		bytes_count += length;
		count++;
		token = _strtok_helper(NULL, delim);

	}
	result[count] = NULL;
	return (result);
}



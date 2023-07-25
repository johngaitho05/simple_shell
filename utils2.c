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
	char *allowed_chars = "0123456789";

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!strchr(allowed_chars, str[i]))
		{
			num = -1;
			break;
		}
		num = num * 10 + (str[i] - 48);
	}
	return (num);
}

/**
 * panic - prints an error message and exits the process
 * @msg: the error message to print
 * @command: the command args array
 * @program: path to the shell as entered by the user
 * @code: exit code
 * Return: 1 to indicate fail
 */
void panic(char *msg, char **command, char *program, int code)
{

	int i = 0;
	char *error;
	int interactive = isatty(STDIN_FILENO);
	char str_code[20];

	if (program)
	{
		if (interactive)
			error = _strncat(program, ": ");
		else
			error = _strncat(program, ": 1: ");
		_puts(error, 2, 0);
	}
	if (command)
	{
		while (command[i])
		{
			error = _strncat(command[i], ": ");
			_puts(error, 2, 0);
			i++;
		}
	}
	_puts(msg, 2, 1);
	free(error); /* _strncat returns a malloc object, so we need to free it */
	sprintf(str_code, "%d", code);
	setenv("EXIT_CODE", str_code, 1);
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
	char *var = NULL;
	char *mypid = malloc(10);

	sprintf(mypid, "%d", getpid());
	if (result == NULL)
	{
		panic("Memory allocation failed", NULL, NULL, 1);
		return (NULL);
	}

	token = _strtok_helper(buffer, delim);
	while (token != NULL)
	{
		token = _strip(token, " \n\r"); /* remove trailing spaces */
		if (_strcmp(token, "$$") == 0)
			token = mypid;
		else if (_strcmp(token, "$?") == 0)
			var = "EXIT_CODE";
		else if (token[0] == '$')
			var = _strip(token, "$"); /* Replace with the actual value */
		if(var)
		{
			token = getenv(var);
			if (!token)
				continue;
		}

		length = _strlen(token);
		required = bytes_count + length;
		if (required > size)
		{
			resized = realloc(result, sizeof(char) * (size + BUFFER_SIZE));
			if (resized == NULL)
				panic("Memory allocation failed",  NULL, NULL, 1);
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

/**
 * _getline - reads a string input from a stream and stores it to a buffer
 * @lineptr: pointer to the buffer
 * @n: size of the buffer that was created
 * @stream: the input
 * Return: number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int ch;
	size_t res = 0, bufsize = *n;
	char *buffer = *lineptr, *resized_buffer;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1); /* Invalid input parameters */
	if (buffer == NULL)
	{
		/* Allocate memory for the buffer initially */
		buffer = (char *)malloc(BUFFER_SIZE);
		if (buffer == NULL)
			return (-1); /* Memory allocation failure */
		bufsize = BUFFER_SIZE;
	}
	while ((ch = fgetc(stream)) != EOF)
	{
		if (res >= bufsize - 1)
		{ /* Make room for the null-terminator */
			bufsize += BUFFER_SIZE;
			resized_buffer = (char *)realloc(buffer, bufsize);
			if (resized_buffer == NULL)
				return (-1); /* Memory allocation failure */
			buffer = resized_buffer;
		}
		buffer[res++] = ch;
		if (ch == '\n' && isatty(STDIN_FILENO))
			break;
	}
	if (res == 0)
		return (-1); /* No data read, or an error occurred */
	buffer[res] = '\0'; /* Null-terminate the string */
	*lineptr = buffer;
	*n = bufsize;
	return (res); /* Return the number of characters read */
}


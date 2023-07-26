#include "main.h"

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
		buffer = (char *)malloc(128);
		if (buffer == NULL)
			return (-1); /* Memory allocation failure */
		bufsize = 128;
	}
	while ((ch = fgetc(stream)) != EOF)
	{
		if (res >= bufsize - 1)
		{ /* Make room for the null-terminator */
			bufsize += 128;
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

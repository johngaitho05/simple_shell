#include "main.h"


/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strlen - Returns the length of a string
 * @s: Pointer to the string to be measured
 *
 * Return: The length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}


/**
 * _strip - remove trailing spaces from string
 * @str: the string to strip
 */
void _strip(char *str)
{
	int length = _strlen(str);

	if (length > 0)
	{
		while (length > 0 && (str[length - 1] == ' ' ||
							  str[length - 1] == '\n' || str[length - 1] == '\r'))
		{
			str[length - 1] = '\0';
			length--;
		}
	}
}


/**
 * _puts - prints a string, followed by a new line, to stdout.
 * @str: the string to print.
 * @add_line_break: whether the string should end with a new line or not.
 * 1 for yes and 0 for no
 * Return: void.
 */
void _puts(char *str, int add_line_break)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	write(STDOUT_FILENO, str, len);
	if (add_line_break)
		write(STDOUT_FILENO, "\n", 1);
}

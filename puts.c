#include "main.h"

/**
 * _puts - prints a string, followed by a new line, to stdout.
 * @str: the string to print.
 * @add_line_break: whether the string should end with a new line or not.
 * @descriptor: Where to print (1 for stdout, 2 for stderror)
 * 1 for yes and 0 for no
 * Return: void.
 */
void _puts(char *str, int descriptor, int add_line_break)
{
	int len = 0;


	while (str[len] != '\0')
		len++;

	write(descriptor, str, len);

	if (add_line_break)
		write(descriptor, "\n", 1);
}

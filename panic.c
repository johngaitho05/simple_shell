#include "main.h"

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

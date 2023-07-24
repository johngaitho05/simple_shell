#include "main.h"

/**
 * handle_env - prints the current environment
 */
void handle_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{

		_puts(*env, 1, 1);
		env++;
	}
	exit(0);
}

/**
 * handle_exit - exit with the given code
 * @command: user input
 * @program: the program name
 */
void handle_exit(char **command, char *program)
{
	int code;
	char *msg;

	if (command[1])
	{
		code = _atoi(command[1]);

		if (code == -1)
		{
			msg = _strncat("Illegal number: ", command[1]);
			command[1] = NULL;
			panic(msg,  command, program, 2);
		}

		exit(code);
	}
	exit(0);
}

/**
 * handle_special - handle special commands
 * @command: user input
 * @program: program name
 */
void handle_special(char **command, char *program)
{
	char *cmd = command[0];


	if (_strcmp(cmd, "env") == 0)
		handle_env();
	/* If the user typed 'exit' then exit gracefully */
	if (_strcmp(cmd, "exit") == 0)
		handle_exit(command, program);
	/* If user typed cd, then call chdir and update PWD value */
	if (_strcmp(cmd, "cd") == 0)
		handle_cd(command, program);
}

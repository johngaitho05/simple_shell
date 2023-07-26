#include "main.h"
#define MAX_PATH_LENGTH 4096

/**
 * _exit_cd - handle_cd helper
 * @cwd: current working directory
 * @owd: old working directory
 */
void _exit_cd(char *cwd, char *owd)
{
	_setenv("PWD", getcwd(cwd, MAX_PATH_LENGTH), 1);
	_setenv("OLDPWD", owd, 1);
	free(cwd);
	free(owd);
}

/**
 * handle_cd - handles change directory command
 * @command: an array containing the arguments of cd
 * @program: the shell path as accessed by the user
 * Return: void
 */
void  handle_cd(char **command, char *program)
{
	char *path, *cwd = NULL, *owd = NULL;

	if (!command[1])
	{
		path = _getenv("HOME");
		if (!path)
			path = getcwd(cwd, MAX_PATH_LENGTH);
	}
	else
		path = command[1];
	if (command[1] && _strcmp(command[1], "-") == 0)
	{
		path = _getenv("OLDPWD");
		if (!path)
		{
			if (!isatty(STDOUT_FILENO))
				path = getcwd(cwd, MAX_PATH_LENGTH);
			else
			{
				command[1] = NULL;
				panic("OLDPWD not set", command, program, 1);
				return;
			}
		}
		if (path)
			_puts(path, 1, 1);
	}
	owd  = getcwd(cwd, MAX_PATH_LENGTH);
	if (chdir(path) == -1)
	{
		if (isatty(STDIN_FILENO))
			panic("No such file or directory", command, program, 0);
		else
		{
			command[1] = NULL;
			panic(_strncat("can't cd to ", path), command, program, 0);
		}
	}
	_exit_cd(cwd, owd);
}

/**
 * handle_env - prints the current environment
 */
void handle_env(void)
{
	int i = 0;

	while (environ[i])
	{

		_puts(environ[i], 1, 1);
		i++;
	}
}

/**
 * handle_exit - exit with the given code
 * @buffer: the command string as typed by the user
 * @command: user input
 * @program: the program name
 * @lines: array of commands extracted from buffer
 */
void  handle_exit(char *buffer, char **command, char *program, char **lines)
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
			return;
		}
		free(command);
		free(lines);
		exit(code);
	}
	free(buffer);
	free(lines);
	free(command);
	exit(0);
}

/**
 * handle_special - handle special commands
 * @buffer: the command string as typed by the user
 * @command: user input
 * @program: program name
 * @lines: array of commands extracted from buffer
 * Return: 0 if the command was executed else -1
 */
int handle_special(char *buffer, char **command, char *program, char **lines)
{
	char *cmd = command[0];
	int i, res = 0;

	if (_strcmp(cmd, "env") == 0)
		handle_env();
		/* If the user typed 'exit' then exit gracefully */
	else if (_strcmp(cmd, "exit") == 0)
		handle_exit(buffer, command, program, lines);
		/* If user typed cd, then call chdir and update PWD value */
	else if (_strcmp(cmd, "cd") == 0)
		handle_cd(command, program);

	else if (_strcmp(cmd, "setenv") == 0)
	{
		if (_arraylen(command) != 3)
		{
			panic("Invalid number of arguments", command, program, 1);
			return (0);
		}
		_setenv(command[1], command[2], 1);
	}
	else if (_strcmp(cmd, "unsetenv") == 0)
	{
		if (!command[1])
		{
			panic("Invalid number of arguments", command, program, 1);
			return (0);
		}
		i = 1;
		while (command[i])
		{
			_unsetenv(command[i]);
			i++;
		}
	}
	else
		res = -1;
	return (res);
}

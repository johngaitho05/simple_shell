#include "main.h"

#define BUFFER_SIZE 128
#define MAX_PATH_LENGTH 4096

/**
 * get_absolute_path - given a command name,
 * this function finds the absolute path to the executable
 * @command: name of the command (str)
 * Return: absolute path to the executable
 */
char *get_absolute_path(const char *command)
{
	FILE *pipe;
	char *result = NULL;
	char buffer[MAX_PATH_LENGTH];
	char cmd[MAX_PATH_LENGTH + 20];

	snprintf(cmd, sizeof(cmd), "which %s", command);
	pipe = popen(cmd, "r");
	if (pipe == NULL)
	{
		perror("popen");
		return (NULL);
	}
	if (fgets(buffer, sizeof(buffer), pipe) != NULL)
	{
		size_t len = _strlen(buffer);

		if (len > 0 && buffer[len - 1] == '\n')
		{
			buffer[len - 1] = '\0';
		}

		result = strdup(buffer);
	}

	pclose(pipe);

	return (result);
}

/**
 * handle_cd - handles change directory command
 * @command: an array containing the arguments of cd
 * @program: the shell path as accessed by the user
 * Return: void
 */
void handle_cd(char **command, char *program)
{
	char *path, *cwd = NULL, *owd = NULL;

	if (!command[1])
		path = getenv("HOME");
	else
		path = command[1];
	if (_strcmp(command[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			command[1] = NULL;
			panic("OLDPWD not set", command, program);
		}
	}

	owd  = getcwd(cwd, MAX_PATH_LENGTH);
	if (chdir(path) == -1)
		panic("No such file or directory", command, program);
	setenv("PWD", getcwd(cwd, MAX_PATH_LENGTH), 1);
	setenv("OLDPWD", owd, 1);
	free(cwd);
}


/**
 * _execute - executes a command given argv and environment variables
 * @command: an array of args where the first arg id the program name
 * @program: the shell path as accessed by the user
 * @env: environment variables
 */
void _execute(char **command, char **env, char *program)
{
	pid_t child_pid;
	int status;
	char *path;



	/* If the user typed 'exit' then exit gracefully */
	if (_strcmp(command[0], "exit") == 0)
	{
		if (command[1])
			exit(_atoi(command[1]));
		exit(0);
	}
	/* If user typed cd, then call chdir and update PWD value */
	if (_strcmp(command[0], "cd") == 0)
		handle_cd(command, program);
	else
	{
		/*
		 * update the first argument of the array
		 * to be an absolute path to the executable
		 */
		path = get_absolute_path(command[0]);
		if (!path)
		{
			if (isatty(STDIN_FILENO))
				program = NULL;
			panic("command not found", command, program);
		}

		command[0] = path;
		child_pid = fork();
		if (child_pid == 0)
			if (execve(command[0], command, env) == -1)
				panic("execve failed!", command, program);

		/* Wait for the child process to execute */
		wait(&status);
	}

}

/**
 * remove_comment - replaces '#' with null thus
 * ignoring everything that comes after
 * @buffer: the input string
 * Return: void
 */
void remove_comment(char *buffer)
{
	int i = 0;

	if(buffer[0] == '#')
		exit(0); /* The whole input is a comment */

	while (buffer[i])
	{
		if (buffer[i] == '#' && buffer[i-1] == ' ')
		{
			buffer[i] = '\0';
		}
		i++;
	}
}

/**
 * execute - executes the command typed typed by user
 * @line: the command to execute
 * @env: an array containing the environment variables
 * @program: the shell path as accessed by the user
 */
void execute(char *line, char **env, char *program)
{
	char **commands, **command;
	int i = 0;

	remove_comment(line);
    if(line == NULL)
		exit(0);
	commands = _strtok(line, ";");
	while (commands[i])
	{
		command = _strtok(commands[i], " ");
		_execute(command, env, program);
		i++;
	}
	free(command);
}



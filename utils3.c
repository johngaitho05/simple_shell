#include "main.h"

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
 * _execute - executes a command given argv and environment variables
 * @command: an array of args where the first arg id the program name
 * @env: environment variables
 */
void _execute(char **command, char **env)
{
	pid_t child_pid;
	int status;

	/* If the user typed 'exit' then exit gracefully */
	if (_strcmp(command[0], "exit") == 0)
		exit(0);

	/*
	 * update the first argument of the array to
	 * be an absolute path to the executable
	 */
	command[0] = get_absolute_path(command[0]);
	if (!command[0])
		panic("command not found");
	child_pid = fork();
	if (child_pid == 0)
		if (execve(command[0], command, env) == -1)
			panic("execve failed!");

	/* Wait for the child process to execute */
	wait(&status);

}

/**
 * execute - executes the command typed typed by user
 * @line: the command to execute
 * @env: an array containing the environment variables
 */
void execute(char *line, char **env)
{
	char **command;

	command = _strtok(line, " ");
	_execute(command, env);
	free(command);
}

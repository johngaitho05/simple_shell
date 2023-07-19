#include "main.h"

#define BUFFER_SIZE 128
#define MAX_PATH_LENGTH 4096

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

void remove_comment(char *buffer)
{
	int i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '#')
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
 */
void execute(char *line, char **env)
{
	char **commands, **command;
	int i = 0;

	remove_comment(line);
	commands = _strtok(line, ";");
	while(commands[i]) {
		command = _strtok(commands[i], " ");
		_execute(command, env);
		i++;
	}
	free(command);
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
		if (ch == '\n')
			break;
	}
	if (res == 0)
		return (-1); /* No data read, or an error occurred */
	buffer[res] = '\0'; /* Null-terminate the string */
	*lineptr = buffer;
	*n = bufsize;
	return (res); /* Return the number of characters read */
}



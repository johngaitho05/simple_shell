#include "main.h"

#define BUFFER_SIZE 128

/**
 * get_absolute_path - given a command name,
 * this function finds the absolute path to the executable
 * @command: name of the command (str)
 * Return: absolute path to the executable
 */
char *get_absolute_path(char *command)
{
	char *path_string = strdup(getenv("PATH")), *dir, *file;
	char **path_dirs = _strtok(path_string, ":");
	int i = 0;
	struct stat file_stat;

	while (path_dirs[i])
	{
		/* Search the executable in the path */
		dir = _strncat(path_dirs[i],  "/");
		file = _strncat(dir, command);
		if (stat(file, &file_stat) == 0)
			if (S_ISREG(file_stat.st_mode))
				return (file);
		i++;
	}

	free(path_dirs);
	return (NULL);

}

/**
 * _execute - executes a command given argv and environment variables
 * @command: an array of args where the first arg id the program name
 * @program: the shell path as accessed by the user
 */
void _execute(char **command, char *program)
{
	pid_t child_pid;
	int status, free_path = 0, special;
	char *path = NULL;
	struct stat file_stat;
	char *cmd = command[0], str_code[20];

	special = handle_special(command, program);

	if (special == 0)
	{
		setenv("EXIT_CODE", "0", 0);
		return; /* It was special command, so we terminate */
	}

	if (stat(cmd, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			path = cmd; /* The passed argument is an absolute file path */
	}
	else
	{
		path = get_absolute_path(cmd);
		free_path = 1;
	}

	if (!path)
	{
		if (isatty(STDIN_FILENO))
			program = NULL;
		panic("not found", command, program, 127);
		return;
	}

	cmd = path;
	child_pid = fork();
	if (child_pid == 0)
		if (execve(cmd, command, environ) == -1)
		{
			panic("execve failed!", command, program, 1);
			return;
		}

	/* Wait for the child process to execute */
	wait(&status);
	sprintf(str_code, "%d", WEXITSTATUS(status));
	setenv("EXIT_CODE", str_code, 1);
	if (free_path)
		free(path);

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

	if (buffer[0] == '#')
		exit(0); /* The whole input is a comment */

	while (buffer[i])
	{
		if (buffer[i] == '#' && buffer[i - 1] == ' ')
		{
			buffer[i] = '\0';
		}
		i++;
	}
}

/**
 * execute - executes the command typed by user
 * @line: the command to execute
 * @program: the shell path as accessed by the user
 */
int execute(char *line, char *program)
{
	char **commands, **command;
	int i = 0;

	remove_comment(line);
	if (line == NULL)
		exit(0);
	commands = _strtok(line, ";");
	while (commands[i])
	{
		command = _strtok(commands[i], " ");
		_execute(command, program);
		i++;
	}
	free(command);
	return (0);
}

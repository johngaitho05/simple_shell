#include "main.h"

/**
 * get_absolute_path - given a command name,
 * this function finds the absolute path to the executable
 * @command: name of the command (str)
 * Return: absolute path to the executable
 */
char *get_absolute_path(char *command)
{
	char *path_string = _strdup(_getenv("PATH")), *dir, *file;
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
			{
				free_tokens(path_dirs, -1);
				free(path_string);
				return (file);
			}
		i++;
	}

	free_tokens(path_dirs, -1);
	free(path_string);
	return (NULL);

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
 * runcmd - execute the command
 * @command: the user input
 * @cmd: path to the executable
 * @program: the shell name as typed by the user
 */
void runcmd(char **command, char *cmd, char *program)
{
	pid_t child_pid;
	int status;
	char str_code[20];

	child_pid = fork();
	if (child_pid == 0)
		if (execve(cmd, command, environ) == -1)
		{
			panic("execve failed!", command, program, 1);
			return;
		}
	wait(&status); /* Wait for the child process to execute */
	_itoa(WEXITSTATUS(status), str_code, 10);
	setenv("EXIT_CODE", str_code, 1);

}

/**
 * _execute - executes a command given argv and environment variables
 * @buffer: the command string as typed by the user
 * @command: an array of args where the first arg id the program name
 * @program: the shell path as typed by the user
 * @lines: array of commands extracted from buffer
 */
void _execute(char *buffer, char **command, char *program, char **lines)
{
	char *path = NULL, *cmd = command[0];
	struct stat file_stat;

	if (handle_special(buffer, command, program, lines) == 0)
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
	}

	if (!path)
	{
		if (isatty(STDIN_FILENO))
			program = NULL;
		panic("not found", command, program, 127);
		return;
	}
	runcmd(command, path, program);
}


/**
 * execute - executes the command typed by user
 * @buffer: the command string as typed by the user
 * @program: the shell path as typed by the user
 * @lines: array of commands extracted from buffer
 * @index: the index of the command to execute
 * Return: 0
 */
int execute(char *buffer, char **lines, int index, char *program)
{
	char **commands, **command, *line = lines[index];
	int i = 0;

	remove_comment(line);
	if (line == NULL)
		exit(0);
	commands = _strtok(line, ";");
	while (commands[i])
	{
		command = _strtok(commands[i], " ");
		_execute(buffer, command, program, lines);
		i++;
		free_tokens(command, -1);
	}
	free_tokens(commands, -1);
	return (0);
}

#include "main.h"

#define MAX_PATH_LENGTH 4096

/**
 * _strtok_helper - computes the next substring
 * given the buffer string and the delimiters
 * @s: the string from which to extract a substring
 * @delim: tokens on which to split the input string
 * Return: the next substring matching the split criteria
 */
char *_strtok_helper(char *s, const char *delim)
{
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;

	if (s == NULL && (s = last) == NULL)
		return (NULL);
	cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;)
	{
		if (c == sc)
			goto cont;
	}
	if (c == 0)
	{
		last = NULL;
		return (NULL);
	}
	tok = s - 1;
	for (;;)
	{
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c)
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
}

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
 *
 * Return: void.
 */
void _puts(char *str, int add_line_break)
{
	int len;

	for (len = 0; str[len] != '\0'; len++);

	write(STDOUT_FILENO, str, len);
	if(add_line_break)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * panic - prints an error message and exist the process
 * @msg: the error message to print
 * Return: 1 to indicate fail
 */
int panic(char *msg)
{
	_puts(msg,1);
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
 * _strtok - splits a string in to substrings based on the
 * specified delimiters and stores the result in an array
 * @buffer: the string to split
 * @delim: the delimiters (a string)
 * Return: an array of substrings
 */
char **_strtok(char *buffer, const char *delim)
{
	int count = 0, size = 100, bytes_count = 0, required, length;
	char **result = malloc(sizeof(char) * 100);
	char **resized, *token;

	if (result == NULL)
		panic("Memory allocation failed");

	token = _strtok_helper(buffer, delim);
	while (token != NULL)
	{
		_strip(token); /* remove trailing spaces */
		length = _strlen(token);
		required = bytes_count + length;
		if (required > size)
		{
			resized = realloc(result, sizeof(char) * (size + 100));
			if (resized == NULL)
				panic("Memory allocation failed");
			result = resized;
			size += 100;
		}
		result[count] = token;
		bytes_count += length;
		count++;
		token = _strtok_helper(NULL, delim);
	}
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

	/* update the first argument of the array to be an absolute path to the executable */
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

int main(int argc __attribute__((unused)),
		 char **argv __attribute__((unused)), char **env)
{
	char *line = NULL;

	size_t len = 0;

	_puts("$",0);
	/* Loop until the user terminates with Ctrl + D */
	/* TODO: implement a custom getline function */
	while (getline(&line, &len, stdin) != -1)
	{
		if (line[0] == '\0' || line[0] == '\n')
			continue;
		execute(line, env);
		_puts("$",0);
	}
	free(line);
	return (0);
}

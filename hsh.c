#include "main.h"


#define MAX_PATH_LENGTH 4096

extern char** environ;

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
	if (c == 0) {
		last = NULL;
		return (NULL);
	}
	tok = s - 1;
	for (;;) {
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
void _puts(char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++);

	write(STDOUT_FILENO, str, len);
	write(STDOUT_FILENO, "\n", 1);
}

int panic(char *s)
{
	_puts(s);
	puts("\n");
	exit(1);
}

char* get_absolute_path(const char* command) {
	FILE* pipe;
	char* result = NULL;
	char buffer[MAX_PATH_LENGTH];

	char cmd[MAX_PATH_LENGTH + 20];
	snprintf(cmd, sizeof(cmd), "which %s", command);

	pipe = popen(cmd, "r");
	if (pipe == NULL) {
		perror("popen");
		return NULL;
	}
	if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
		}

		result = strdup(buffer);
	}

	pclose(pipe);

	return result;
}

char **_strtok(char *buffer, const char *delim)
{
	int count = 0, size = 100, bytes_count = 0, required, length;
	char **command = malloc(sizeof(char) * 100);
	char **resized, *token;

	if(command == NULL)
		panic("Memory allocation failed");

	token = _strtok_helper(buffer, delim);
	while (token != NULL)
	{
		_strip(token); /* remove trailing spaces */
		length = _strlen(token);
		required = bytes_count + length;
		if (required > size)
		{
			resized = realloc(command, sizeof(char) * (size + 100));
			if(resized == NULL)
				panic("Memory allocation failed");
			command = resized;
			size += 100;
		}
		command[count] = token;
		bytes_count += length;
		count++;
		token = _strtok_helper(NULL, delim);
	}
	return (command);
}


int main(void) {

	pid_t child_pid;
	char **command, buffer[] = "ls";
	int status;

	command = _strtok(buffer, " ");

	command[0] = get_absolute_path(command[0]);
	child_pid = fork();
	if (child_pid == 0)
		if (execve(command[0], command, environ) == -1)
			panic("execve failed!");

	wait(&status);
	free(command);
	return 0;
}

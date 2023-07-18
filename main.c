#include "main.h"


/**
 * main - entry point for the shell
 * @argc: number of args
 * @argv: command line arguments
 * @env: environment variables
 * Return: 0 on success, 1 on failure
 */
int main(int argc __attribute__((unused)),
		 char **argv __attribute__((unused)), char **env)
{
	char *line = NULL;

	size_t len = 0;

	_puts("$", 0);
	/* Loop until the user terminates with Ctrl + D */
	/* TODO: implement a custom getline function */
	while (getline(&line, &len, stdin) != -1)
	{
		if (line[0] == '\0' || line[0] == '\n')
			continue;
		execute(line, env);
		_puts("$", 0);
	}
	free(line);
	return (0);
}

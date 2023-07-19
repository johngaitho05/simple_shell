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
	int interactive = isatty(STDIN_FILENO);
	size_t len = 0;

	if (interactive)
		/* only print the prompt if the shell is launched in interactive mode */
		_puts("$", 0);

	/* Loop until the user terminates with Ctrl + D */
	while (_getline(&line, &len, stdin) != -1)
	{
		if (line[0] == '\0' || line[0] == '\n')
			continue;
		execute(line, env);
		_puts("$", 0);
	}
	free(line);
	return (0);
}

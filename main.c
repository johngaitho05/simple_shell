#include "main.h"

/**
 * main - entry point for the shell
 * @argc: number of args
 * @argv: command line arguments
 * Return: 0 on success, 1 on failure
 */
int main(int argc __attribute__((unused)),
		 char **argv __attribute__((unused)))
{
	char *line = NULL, **lines, *program = "bash", *code_str;
	int interactive = isatty(STDIN_FILENO);
	size_t len = 0;
	int i = 0, code = 0;

	if (!interactive)
		program = argv[0];
	/* Loop until the user terminates with Ctrl + D */
	while (_getline(&line, &len, stdin) != -1)
	{
		lines = _strtok(line, "\n");
		while (lines[i])
		{
			if (lines[i][0] == '\0' || lines[i][0] == '\n')
				continue;
			execute(lines[i], program);
			code_str = getenv("EXIT_CODE");
			if (code_str)
				code = _atoi(code_str);
			if (code && !interactive)
			{
				unsetenv("EXIT_CODE");
				exit(code);
			}
			i++;
		}
		if (!interactive)
		{
			code = _atoi(getenv("EXIT_CODE"));
			unsetenv("EXIT_CODE");
			exit(code);
		}
		unsetenv("EXIT_CODE");
		i = 0;
	}
	unsetenv("EXIT_CODE");
	if (line != NULL)
		free(line);
	return (0);
}

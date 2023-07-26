#include "main.h"

/**
 * terminate - terminates the program
 * @line: user input buffer
 * @lines: array of commands
 */
void terminate(char **lines, char *line)
{
	int code = 0;
	char *code_str;

	code_str = getenv("EXIT_CODE");
	if (code_str)
		code = _atoi(code_str);

	unsetenv("EXIT_CODE");
	if (lines != NULL)
		free(lines);
	if (line != NULL)
		free(line);

	exit(code);
}

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
			execute(line, lines, i, program);
			code_str = getenv("EXIT_CODE");
			if (code_str)
				code = _atoi(code_str);
			if (code && !interactive)
				terminate(lines, line);
			i++;
		}
		if (!interactive)
			terminate(lines, line);
		i = 0;
		free(lines);
	}
	free(line);
	return (0);
}

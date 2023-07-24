#ifndef SIMPLE_SHELL2_MAIN_H
#define SIMPLE_SHELL2_MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sys/unistd.h"
#include "sys/wait.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "string.h"
#include "syscall.h"

char *_strtok_helper(char *s, const char *delim);
int _strlen(char *s);
char  *_strip(char *str, char *tokens);
void _puts(char *str, int descriptor, int add_line_break);
char *get_absolute_path(char *command);
void handle_env(void);
void handle_exit(char **command, char *program);
void handle_special(char **command, char *program);
void _execute(char **command, char *program);
void execute(char *line, char *program);
int panic(char *msg, char **command, char *program, int code);
int _strcmp(char *s1, char *s2);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _atoi(char *str);
void handle_cd(char **command, char *program);
char *_strncat(char *s1, char *s2);
char **_strtok(char *buffer, const char *delim);

extern char **environ;

#endif

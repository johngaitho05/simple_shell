#ifndef SIMPLE_SHELL2_MAIN_H
#define SIMPLE_SHELL2_MAIN_H

#define MAX_PATH_LENGTH 4096


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
void _strip(char *str);
void _puts(char *str, int add_line_break);
char **_strtok(char *buffer, const char *delim);
void _execute(char **command, char **env);
char *get_absolute_path(const char *command);
void execute(char *line, char **env);
int panic(char *msg);
int _strcmp(char *s1, char *s2);


#endif

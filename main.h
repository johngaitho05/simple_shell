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
void _strip(char *str);
void _puts(char *str);
char **_strtok(char *buffer, const char *delim);

extern char **environ;

#endif

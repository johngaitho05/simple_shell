#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "unistd.h"
#include "wait.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "syscall.h"

extern char **environ;

int _atoi(char *str);
void reverse(char str[], int length);
int _strlen(char *s);
int _arraylen(char **array);
char *_itoa(int num, char str[], int base);
char *_strncat(char *s1, char *s2);
char *_strcpy(char* dest, const char* src);
int _strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
void *_memmove(void *dest, const void *src, size_t n);
char *_strdup(char *str);
char  *_strip(char *str, char *tokens);
void _puts(char *str, int descriptor, int add_line_break);
char *_strtok_helper(char *s, const char *delim);
char **_strtok(char *buffer, const char *delim);
char *get_absolute_path(char *command);
char *update_token(char *token);
void handle_env(void);
void handle_exit(char **command, char *program);
void handle_cd(char **command, char *program);
int handle_special(char **command, char *program);
void _execute(char **command, char *program);
int execute(char *line, char *program);
void panic(char *msg, char **command, char *program, int code);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif

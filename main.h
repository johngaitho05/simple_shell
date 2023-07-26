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
#include "syscall.h"

int _atoi(char *str);
void reverse(char str[], int length);
int _strlen(char *s);
int _arraylen(char **array);
char *_itoa(int num, char str[], int base);
char *_strncat(char *s1, char *s2);
char *_strcpy(char* dest, const char* src);
int _strchr(char *s, char c);
void *_memmove(void *dest, const void *src, size_t n);
char *_strdup(char *str);
char  *_strip(char *str, char *tokens);
void _puts(char *str, int descriptor, int add_line_break);
char *get_absolute_path(char *command);
char *update_token(char *token);
char *_strtok_helper(char *s, const char *delim);
char **_strtok(char *buffer, const char *delim);
void handle_env(void);
void handle_exit(char **command, char *program);
void handle_cd(char **command, char *program);
int handle_special(char **command, char *program);
void _execute(char **command, char *program);
int execute(char *line, char *program);
void panic(char *msg, char **command, char *program, int code);
int _strcmp(char *s1, char *s2);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

extern char **environ;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 128
#endif

#endif

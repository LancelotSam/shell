#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define MAX_TOTAL_LENGTH 1024
#define MAX_PATHS 10

void my_shell();
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
const char *_strtok(const char *str, const char *delim);
const char *_strchr(const char *str, int c);
char *_strncpy(char *dest, const char *src, size_t n);
const char *_strchr(const char *str, int c);
const char *_strtok(const char *str, const char *delim);
char *_strdup(const char *src);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *str);
int _strcmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);
int _atoi(const char *str);
int my_exit(char *args[]);

#endif

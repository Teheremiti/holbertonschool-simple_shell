#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
void free_argv(char **);
char *_getenv(const char *);
void _which(const char *);

#endif

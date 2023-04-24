#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
char **arrstrdup(char **arr);
int get_argc(char *);
char **get_argv(char *, int);
void free_arr(char **);
char *_getenv(const char *);
char *_which(char *);
int execute(int, char *, char *, char **);

#endif

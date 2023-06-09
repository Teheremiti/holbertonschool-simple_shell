#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
int get_argc(char *);
char **get_argv(char *, int);
void free_arr(char **);
void free_argv(int argc, char **argv);
char *_getenv(const char *);
char *_which(char *);
int execute(int, char *, char **);
int _env(int);
void printOops(void);

#endif

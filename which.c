#include "main.h"

/**
 * _getenv - Get the value of a environment variable if it exists
 *
 * @name: Variable to check
 *
 * Return: The value of the variable if it exists, otherwise NULL
 */

char *_getenv(const char *name)
{
	int i;
	char *token;

	for (i = 0; environ[i]; i++)
	{
		char *env_cpy = strdup(environ[i]);

		if (env_cpy == NULL)
			printOops();

		token = strtok(env_cpy, "=");
		if (strcmp(token, name) == 0)
		{
			char *result;

			token = strtok(NULL, "\0");
			if (token == NULL)
			{
				free(env_cpy);
				return (NULL);
			}

			result = strdup(token);
			if (result == NULL)
			{
				free(env_cpy);
				printOops();
			}

			free(env_cpy);
			return (result);
		}
		free(env_cpy);
	}
	return (NULL);
}


/**
 * _which - Get the path of a file
 *
 * @file: Name of the file to look for
 *
 * Return: The path to the file if it exists, otherwise NULL
 */

char *_which(char *file)
{
	struct stat status;
	char *env_path, *pathCopy, *filepath, *dir;

	if (file[0] == '/' || file[0] == '.')
		if (stat(file, &status) == 0 && access(file, X_OK) == 0)
			return (file);

	env_path = _getenv("PATH");
	if (env_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", file);
		return (NULL);
	}

	pathCopy = strdup(env_path);
	if (pathCopy == NULL)
		free(env_path), printOops();

	free(env_path), env_path = NULL;
	dir = strtok(pathCopy, ":");
	while (dir)
	{
		filepath = malloc(512);
		sprintf(filepath, "%s/%s", dir, file);

		if (stat(filepath, &status) == 0 && access(filepath, X_OK) == 0)
		{
			free(pathCopy), pathCopy = NULL;
			return (filepath);
		}

		free(filepath), filepath = NULL;
		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", file);
	free(pathCopy), pathCopy = NULL;
	return (NULL);
}


/**
 * _env - env built-in
 *
 * @pid: Id of the calling process
 *
 * Return: -1 on failure, otherwise 0
 */

int _env(int pid)
{
	char *argv[] = {"/usr/bin/env", NULL};
	int status;

	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
			return (-1);
	}

	else
		wait(&status);

	return (0);
}


/**
 * printOops - Print an error message after a failed malloc
 *
 * Return: (void)
 */

void printOops(void)
{
	fprintf(stderr, "Oops, something went wrong :(\nPlease try again\n");
	exit(98);
}

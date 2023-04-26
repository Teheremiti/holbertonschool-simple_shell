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

		token = strtok(env_cpy, "=");
		if (strcmp(token, name) == 0)
		{
			char *result;

			token = strtok(NULL, "\0");
			result = strdup(token);
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
 * Return: The path to the file if it exists, otherwise nothing
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
		fprintf(stderr, "./hsh: :1 %s: not found\n", file);
		exit(127);
	}

	pathCopy = strdup(env_path);
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

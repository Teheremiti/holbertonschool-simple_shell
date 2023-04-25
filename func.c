#include <sys/types.h>
#include <sys/stat.h>
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
 * _which - Look for files in the current PATH
 *
 * @filename: File to look for
 *
 * Return: The path of the file if it exists, otherwise NULL
 */

char *_which(char *filename)
{
	char *path, *path_cpy, *file_path, *dir;
	struct stat status;

	if (filename[0] == '/' || filename[0] == '.')
	{
		printf("filename: %s\n", filename);
		file_path = strdup(filename);
	}

	path = _getenv("PATH");
	if (path == NULL && (filename[0] != '/' && filename[0] != '.'))
	{
		fprintf(stderr, "./hsh: :1 %s: not found\n", filename);
		exit(127);
	}

	path_cpy = strdup(path), free(path);
	dir = strtok(path_cpy, ":");
	while (dir)
	{
		if (filename[0] != '/' && filename[0] != '.')
		{
			file_path = malloc(512);
			sprintf(file_path, "%s/%s", dir, filename);
		}

		if (stat(file_path, &status) == 0 && access(file_path, X_OK) == 0)
		{
			free(path_cpy);
			return (file_path);
		}

		if (filename[0] != '/' && filename[0] != '.')
			free(file_path);

		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", filename);
	free(path_cpy);
	if (filename[0] == '/' || filename[0] == '.')
		free(file_path);

	return (NULL);
}

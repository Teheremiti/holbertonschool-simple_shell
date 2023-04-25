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

	path = _getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not found\n");
		exit(1);
	}

	path_cpy = strdup(path), free(path);
	dir = strtok(path_cpy, ":");
	while (dir)
	{
		int flag_stat, flag_access;

		if (filename[0] == '/')
			file_path = strdup(filename);
		else
		{
			file_path = malloc(512);
			sprintf(file_path, "%s/%s", dir, filename);
		}

		flag_stat = stat(file_path, &status);
		flag_access = access(file_path, X_OK);

		if (flag_stat == 0 && flag_access == 0)
		{
			free(path_cpy);
			return (file_path);
		}

		free(file_path), file_path = NULL;
		dir = strtok(NULL, ":");
	}

	printf("%s: command not found\n", filename);
	free(path_cpy);
	return (NULL);
}

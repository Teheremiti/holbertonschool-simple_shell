#include "main.h"
#include <sys/wait.h>

/**
 * free_argv - Free an argv
 *
 * @argv: argv to free
 *
 * Return: (void)
 */

void free_argv(char **argv)
{
	int i = 0;

	for (; argv[i] != NULL; i++)
	{
		free(argv[i]);
		argv[i] = NULL;
	}

	free(argv);
	argv = NULL;
}


/**
 * main - Simple shell
 *
 * Return: 0 on SUCCESS
 */

int main(void)
{
	char *cmd = NULL, *cmd_cpy = NULL, *token = NULL;
	char *sep = " ., \t\n";
	char **argv = NULL;
	int i = 0, pid, argc;
	size_t n;

	printf("$ ");

	while (getline(&cmd, &n, stdin) != -1)
	{
		cmd_cpy = strdup(cmd);

		argc = 0;
		token = strtok(cmd, sep);
		while (token)
		{
			token = strtok(NULL, sep);
			argc++;
		}
		if (argc == 0)
		{
			printf("$ ");
			continue;
		}

		argv = malloc(sizeof(char *) * (argc + 1));

		i = 0;
		token = strtok(cmd_cpy, sep);
		while (token)
		{
			argv[i] = strdup(token);
			token = strtok(NULL, sep);
			i++;
		}
		argv[i] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("Error fork()");
			free(cmd), free(cmd_cpy), free_argv(argv);
			return (-1);
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("Error execve()");
				free(cmd), free(cmd_cpy), free_argv(argv);
				return (-1);
			}
		}
		else
			wait(NULL);

		printf("$ ");
	}

	free(cmd), free(cmd_cpy), free_argv(argv);
	cmd = NULL, cmd_cpy = NULL;
	return (0);
}

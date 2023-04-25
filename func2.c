#include <sys/wait.h>
#include "main.h"

/**
 * get_argc - Get the number of arguments in the command line
 *
 * @cmd: Command line
 *
 * Return: The number of arguments in cmd
 */

int get_argc(char *cmd)
{
	char *sep = " ,\t\n";
	char *token = NULL;
	int argc = 0;

	token = strtok(cmd, sep);
	while (token)
	{
		token = strtok(NULL, sep);
		argc++;
	}

	return (argc);
}


/**
 * get_argv - Get argument vector
 *
 * @cmd: Input to split
 * @argc: Argument count
 *
 * Return: Split arguments
 */

char **get_argv(char *cmd, int argc)
{
	char *sep = " ,\t\n";
	int i = 0;
	char *token = strtok(cmd, sep);
	char **argv = malloc(sizeof(char *) * (argc + 1));

	while (token)
	{
		argv[i] = strdup(token);
		token = strtok(NULL, sep);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}


/**
 * free_arr - Free an array of strings
 *
 * @arr: Array to free
 *
 * Return: (void)
 */

void free_arr(char **arr)
{
	int i = 0;

	for (; arr[i] != NULL; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr);
	arr = NULL;
}


/**
 * execute - Execute the command in the child process
 *
 * @pid: Pid of process
 * @cmd: Input from command line
 * @cmd_cpy: Command line copy
 * @argv: Argument vector
 * *
 * Return: -1 on failure, otherwise nothing
 */

int execute(int pid, char *cmd, char *cmd_cpy, char **argv)
{
	if (pid == -1)
	{
		perror("Error fork()");
		free(cmd), free(cmd_cpy), free_arr(argv);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
		{
			perror("Error execve()");
			free(cmd), free(cmd_cpy), free_arr(argv);
			return (-1);
		}
	}
	else
		wait(NULL);

	return (-1);
}

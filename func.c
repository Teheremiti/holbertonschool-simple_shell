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
	char **argv = malloc((argc + 1) * sizeof(char *));

	while (token)
	{
		argv[i] = strdup(token);
		if (argv[i] == NULL)
		{
			free_arr(argv);
			printOops();
			exit(98);
		}

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
 * free_argv - Free argv with special cases
 *
 * @argc: Argument count
 * @argv: Argument vector to free
 *
 * return: (void)
 */

void free_argv(int argc, char **argv)
{
	if (argc > 1 && (argv[0][0] != '/' && argv[0][0] != '.'))
		free_arr(argv);

	else if (argc == 1 && (argv[0][0] != '/' && argv[0][0] != '.'))
		free(argv[0]), free(argv);

	else
		free(argv[1]), free(argv);
}


/**
 * execute - Execute the command in the child process
 *
 * @pid: Pid of process
 * @cmd: Command to execute
 * @argv: Argument vector
 *
 * Return: -1 on failure, otherwise the exit status of the command ran
 */

int execute(int pid, char *cmd, char **argv)
{
	int status;

	if (pid == -1)
	{
		free_arr(argv);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
		{
			free_arr(argv);
			return (-1);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (0);
}

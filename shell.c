#include "main.h"
#include <sys/wait.h>

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
 * execute - Execute the command in the child process
 *
 * @pid: Pid of process
 * @cmd: Input from command line
 * @cmd_cpy: Command line copy
 * @argv: Argument vector
 *
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


/**
 * main - Simple shell
 *
 * Return: 0 on SUCCESS, otherwise 1
 */

int main(void)
{
	char *cmd = NULL, *cmd_cpy = NULL;
	char **argv = NULL;
	int pid, argc;
	size_t n;

	/* printf("$ "); */

	while (getline(&cmd, &n, stdin) != -1)
	{
		cmd_cpy = strdup(cmd);

		argc = get_argc(cmd);
		if (argc == 0)
		{
			free(cmd_cpy);
			continue;
		}

		argv = get_argv(cmd_cpy, argc);
		cmd = _which(argv[0]);
		if (cmd == NULL)
		{
			free(cmd), free(cmd_cpy);
			return (1);
		}

		pid = fork();
		execute(pid, cmd, cmd_cpy, argv);

		/* printf("$ "); */
		free(cmd_cpy), free_arr(argv);
	}

	free(cmd);
	cmd = NULL, cmd_cpy = NULL;
	return (0);
}

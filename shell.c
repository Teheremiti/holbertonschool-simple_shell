#include "main.h"

/**
 * main - Simple shell
 *
 * Return: 0 on SUCCESS, otherwise 1
 */

int main(void)
{
	char *cmd = NULL, *cmd_cpy = NULL, *file = NULL;
	char **argv = NULL;
	int pid, argc;
	size_t n;

	while (getline(&cmd, &n, stdin) != -1)
	{
		cmd_cpy = strdup(cmd);

		argc = get_argc(cmd_cpy);
		if (argc == 0)
		{
			free(cmd), free(cmd_cpy);
			continue;
		}

		argv = get_argv(cmd, argc);
		free(cmd), free(cmd_cpy), cmd = NULL, cmd_cpy = NULL;

		file = _which(argv[0]);
		if (file == NULL)
		{
			free_arr(argv);
			exit(127);
		}

		pid = fork();
		execute(pid, file, argv);

		free_arr(argv);
	}

	free(cmd);
	cmd = NULL, cmd_cpy = NULL;
	return (0);
}

#include "main.h"

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
			free(cmd), free(cmd_cpy);
			continue;
		}

		argv = get_argv(cmd_cpy, argc);
		free(cmd);
		cmd = _which(argv[0]);
		if (cmd == NULL)
		{
			free(cmd), free(cmd_cpy), free(argv);
			continue;
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

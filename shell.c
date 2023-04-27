#include "main.h"

/**
 * main - Simple shell
 *
 * Return: 0 on SUCCESS, otherwise nothing  and exits with appropriate status
 */

int main(void)
{
	char *cmd = NULL, *cmd_cpy = NULL, *file = NULL;
	char **argv = NULL;
	int pid, argc, flag = 0;
	size_t n;

	while (getline(&cmd, &n, stdin) != -1)
	{
		if (strcmp(cmd, "exit\n") == 0)
			free(cmd), exit(flag);
		if (strcmp(cmd, "env\n") == 0)
		{
			pid = fork(), _env(pid);
			continue;
		}
		cmd_cpy = strdup(cmd);
		if (cmd_cpy == NULL)
			free(cmd), printOops();
		argc = get_argc(cmd_cpy);
		if (argc == 0)
		{
			free(cmd_cpy);
			continue;
		}

		argv = get_argv(cmd, argc);
		free(cmd), free(cmd_cpy), cmd = NULL, cmd_cpy = NULL;

		file = _which(argv[0]);
		if (file == NULL)
			free_arr(argv), exit(127);

		pid = fork();
		flag = execute(pid, file, argv);

		free_argv(argc, argv), free(file), file = NULL;
	}

	free(cmd), free(file);
	return (0);
}

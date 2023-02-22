#include "main.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **argv, char **front, int *exe_ret);
int run_args(char **argv, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **argv);

/**
 * get_args - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - Partitions operators from commands and calls them.
 * @argv: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_args(char **argv, char **front, int *exe_ret)
{
	int ret, index;

	if (!argv[0])
		return (*exe_ret);
	for (index = 0; argv[index]; index++)
	{
		if (_strncmp(argv[index], "||", 2) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			argv = replace_aliases(argv);
			ret = run_args(argv, front, exe_ret);
			if (*exe_ret != 0)
			{
				argv = &argv[++index];
				index = 0;
			}
			else
			{
				for (index++; argv[index]; index++)
					free(argv[index]);
				return (ret);
			}
		}
		else if (_strncmp(argv[index], "&&", 2) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			argv = replace_aliases(argv);
			ret = run_args(argv, front, exe_ret);
			if (*exe_ret == 0)
			{
				argv = &argv[++index];
				index = 0;
			}
			else
			{
				for (index++; argv[index]; index++)
					free(argv[index]);
				return (ret);
			}
		}
	}
	argv = replace_aliases(argv);
	ret = run_args(argv, front, exe_ret);
	return (ret);
}

/**
 * run_args - Calls the execution of a command.
 * @argv: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **argv, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **argv, char **front);

	builtin = get_builtin(argv[0]);

	if (builtin)
	{
		ret = builtin(argv + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(argv, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; argv[i]; i++)
		free(argv[i]);

	return (ret);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **argv, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	argv = _strtok(line, " ");
	free(line);
	if (!argv)
		return (ret);
	if (check_args(argv) != 0)
	{
		*exe_ret = 2;
		free_args(argv, argv);
		return (*exe_ret);
	}
	front = argv;

	for (index = 0; argv[index]; index++)
	{
		if (_strncmp(argv[index], ";", 1) == 0)
		{
			free(argv[index]);
			argv[index] = NULL;
			ret = call_args(argv, front, exe_ret);
			argv = &argv[++index];
			index = 0;
		}
	}
	if (argv)
		ret = call_args(argv, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @argv: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **argv)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; argv[i]; i++)
	{
		cur = argv[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&argv[i], 2));
			nex = argv[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&argv[i + 1], 2));
		}
	}
	return (0);
}

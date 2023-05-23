#include "shell.h"
/**
 * main - reading the input from te user and displays it back
 * @argc: number of arguments
 * @argv: arguments
 * @env: enviromt variable
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	char *string, **arg;
	size_t n = 100;

	string = malloc(sizeof(char) * n);
	while (1)
	{
		prompt();
		if (getline(&string, &n, stdin) == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (string == NULL)
			continue;
		arg = _strtok(string);
		if (arg == NULL)
		{
			continue;
		}
		if (_strcmp(arg[0], "env") == 0)
			print_env(env);
		else if (_strcmp(arg[0], "exit") == 0)
			exit(98);
		else
			_exec(arg, argv, env);
		free_maloc(arg);
	}
	free(string);
	return (0);
}
/**
 * prompt - displays the terminal
 *
 * Return: nothing
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		write(STDOUT_FILENO, "$ ", 2);
	}

}
/**
 * free_maloc - frees pointer to pointer
 * dynamic allocation
 * @array: double pointer
 * Return: nothing
 */
void free_maloc(char **array)
{
	int j = 0;

	while (array[j] != NULL)
	{
		j++;
	}
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
}
/**
 * _exec - executes the executable commands
 * @arg: command and arguments
 * @argv: arguments to main
 * @env: enviromental variable
 * Return: nothing
 */
void _exec(char **arg, char **argv, char **env)
{
	pid_t pid;
	char *cmd;
	int status;

	cmd = _strdup(arg[0]);
	free(arg[0]);
	arg[0]  = get_folder(cmd, env);
	free(cmd);
	if (cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(arg[0], arg, env) == -1)
				perror(argv[0]);
		}
		else if (pid > 0)
			wait(&status);
		else
			perror(argv[0]);
	}
	else
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, arg[0], _strlen(arg[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
}

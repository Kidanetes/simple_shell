#include "shell.h"
/**
 * print_env - print te enviromental variables
 * env - pointer to env. variables
 *
 * Return: nothing
 */
void print_env(char **env);
void print_env(char **env)
{
	int i = 0;

	while (env != NULL && env[i] != NULL)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
void free_maloc(char **array);
void prompt(void);
/**
 * main - reading the input from te user and displays it back
 *
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char *string, **arg;
	int /*j,*/ status;
	size_t n = 100;

	string = malloc(sizeof(char) * n);
	/*write(STDOUT_FILENO, "$ ", 2);*/
	while (1)
	{
		prompt();

		/**if (isatty(STDIN_FILENO) == 1)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}*/
		if (getline(&string, &n, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (string == NULL)
		{
			continue;
		}
		/*j = 0;*/
		arg = _strtok(string);
		if (arg == NULL)
		{
			continue;
		}

		/**while (array != NULL && array[j] != NULL)
		{
			printf("%s\n", array[j]);
			j++;
		}*/
		
		
		if (fork() == 0)
		{
			if (execv(arg[0], arg) == -1)
			{
				write(STDERR_FILENO, argv[0], _strlen(argv[0]));
				write(STDERR_FILENO, ": ", 2);
				perror(arg[0]);
			}
		}
		else 
			wait(&status);
		free_maloc(arg);
		/**while (arg[j] != NULL)
		{
			j++;
		}
		while (j >= 0)
		{
			free(arg[j]);
			j--;
		}*/
		/*write(STDOUT_FILENO, "$ ", 2);*/
		/**free(arg);*/
		
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

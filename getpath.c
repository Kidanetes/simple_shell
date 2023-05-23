#include "shell.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
extern char **environ;
char *get_path(void);
char **str_tok(char *str);
char *get_folder(char *input);
int _number_of_words(char *str);
void free_maloc(char **array);
/**
 * get_path - gets the value of Path variable
 *
 * Return: string of the path variable
 */
char *get_path(void)
{
	char *str = "PATH";
	char *path;
	int i = 0, j, len, k;

	while (environ[i] != NULL)
	{
		
		j = 0;
		while (j < 4)
		{
			if (environ[i][j] != str[j])
				break;
			j++;
		}
		if (j == 4)
		{
			k = 0;
			len = _strlen(environ[i]) - 5;
			path = malloc(sizeof(char) *(len + 1));
			while (k < len )
			{
				path[k] = environ[i][k + 5];
				k++;
			}
			path[k] = '\0';
			return (path);
		}
		i++;
	}
	return (NULL);
}

/**
 * get_folder - find the location of the comman
 * @input: comman input from the terminal
 *
 * Return: the path of the command
 */
char *get_folder(char *input)
{
	struct stat ptr;
	int i = 0;
	char *cmd1, *cmd2, *cmd3;
	char *path, **dir;

	if (stat(input, &ptr) == 0)
		return (input);
	path = get_path();
	if (path != NULL)
	{
		dir = str_tok(path);
		free(path);
		while (dir != NULL && dir[i] != NULL)
		{
			cmd1 = _strdup(dir[i]);
			cmd2 = str_concat(cmd1, "/");
			cmd3 = str_concat(cmd2, input);
			free(cmd1);
			free(cmd2);
			if (stat(cmd3, &ptr) == 0)
			{
				free_maloc(dir);
				return (cmd3);
			}
			else
				free(cmd3);
			i++;
		}
		free_maloc(dir);
		return (NULL);
	}
	return (NULL);
}
/**
 * _number_of_words - number of words
 * @str: input string
 *
 * Return: number of words
 */
int _number_of_words(char *str)
{
	int i = 1, j = 0;

	while (str[j] != '\0')
	{
		if (str[j] == ':'  && str[j + 1] != '\0')
			i++;
		j++;
	}
	return (i);
}
/**
 * str_tok - tokinize the PATH enviromental variable
 * @path: value of the PATH variable
 *
 * Return: ppointer to tokens of Path variable
 */
char **str_tok(char *str)
{
	int j = 0, i, len = 0;
	char **array, *token;

	if (str == NULL)
		return (NULL);
	i = _number_of_words(str);
	if (i == 0)
		return (NULL);
	array = malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	token = strtok(str, ":");
	while (token != NULL)
	{
		len = _strlen(token);
		array[j] = malloc(sizeof(char) * (len + 1));
		if (array[j] == NULL)
		{
			while (--j)
				free(array[j]);
			free(array);
			return (NULL);
		}
		i = 0;
		while (token[i] != '\0')
		{
			array[j][i] = token[i];
			i++;
		}
		array[j][i] = '\0';
		j++;
		token = strtok(NULL, ":");
	}
	array[j] = NULL;
	return (array);
}

int main(int argc __attribute__((unused)), char **argv)
{
	char *input = "cd";
	char *ptr;

	ptr = get_folder(input);
	if (ptr != NULL)
		printf("%s$\n",ptr);
	else 
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, input, _strlen(input));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	free(ptr);
	return (0);
}
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

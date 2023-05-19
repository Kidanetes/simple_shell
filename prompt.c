#include "shell.h"
/**
 * main - reading the input from te user and displays it back
 *
 * Return: 0
 */
int main(void)
{
	char *string, **array;
	int j;
	size_t n = 100;

	string = malloc(sizeof(char) * n);
	printf("$ ");
	while (getline(&string, &n, stdin) != -1)
	{
		j = 0;
		printf("%s", string);
		array = _strtok(string);
		while (array != NULL && array[j] != NULL)
		{
			printf("%s\n", array[j]);
			j++;
		}
		while (j >= 0)
		{
			free(array[j]);
			j--;
		}
		free(array);
		printf("$ ");
	}
	printf("\n");
	free(string);
	return (0);
}

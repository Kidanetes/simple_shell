#include "shell.h"
extern char **environ;
char *get_path(void);
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






		

			
		




	



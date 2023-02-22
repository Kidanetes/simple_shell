#include "simple_shell.h"
/**
 * _strdup - copes a string to another
 * @str: the array
 * Return: pointer of sting copied
 */
char *_strdup(char *str)
{
	int i, j;
	char *s = NULL;

	if (str == NULL)
		return (0);
	for (i = 0; str[i]; i++)
		;
	i++;
	s = malloc(i * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0; j < i; j++)
	{
		s[j] = str[j];
	}
	return (s);
}
/**
 * _calloc - allocates memory for array
 * @nmemb: input parameter1
 * @size: input parameter2
 * Return: pointer
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *p;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);

	for (i = 0; i < nmemb * size; i++)
		p[i] = 0;

	return (p);

}
/**
 * func_printenv - prints the current environment
 * @environ: environment variable
 * Return: void
 */
void func_printenv(char **environ)
{
	int i = 0;

	for (; environ[i] ; i++)
		_puts(environ[i]);
}
/**
 * handle_signal - prints new line and prompt when CTRL + C is passed as input
 * @signal: name of sig
 * Return: void
 */
void handle_signal(int signal)
{
	char *prompt = {"\n{$} "};
	(void) signal;

	write(STDOUT_FILENO, prompt, _strlen(prompt));
	fflush(stdout);
}

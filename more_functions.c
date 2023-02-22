#include "simple_shell.h"
/**
 * _strdup -  copy the string given as a parameter
 * @str: input parameter
 * Return: pointer to copied string
 */
char *_strdup(char *str)
{
	int size, i = 0;
	char *array;

	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		i++;
	}
	size = i + 1;
	array = malloc(size);
	if (array == NULL)
		return (NULL);
	for (i = 0; i < size; i++, str++)
		array[i] = *str;
	array[i] = '\0';
	return (array);
}
/**
 * _calloc - allocates memory for array
 * @nmemb: input parameter1
 * @size: input parameter2
 * Return: pointer
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned int i;
	void *ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	for (i = 0; i < nmemb * size; i++)
		*((char *)(ptr) + i) = 0;
	return (ptr);
}
/**
 * _itoa - integer to ascii
 * @num: num
 * @base: base
 * Return: char
 */
char *_itoa(int num, int base)
{
	static char *array = "0123456789abcdef";
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (num < 0)
	{
		n = -num;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	do      {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
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
		_puts(environ[i]); /*imprime todo el environment*/
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

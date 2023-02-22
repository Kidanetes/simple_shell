#include "simple_shell.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _puts - prints a string
 * @str: input parameter
 * Return: void
 */
void _puts(char *str)
{
	int i;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		_putchar(*(str + i));
	}
	_putchar('\n');
}
/**
 * _strlen - returns the length of a string
 * @s: input parameter
 * Return: int
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; *(s + i) != '\0'; i++)
	{
	}

	return (i);
}
/**
 * _strcmp - compares two strings
 * @s1: input parameter
 * @s2: input parameter
 * Return: Integer
 */
int _strcmp(char *s1, char *s2)
{
	int num = 0;
	int i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	num = s1[i] - s2[i];

	return (num);
}
/**
 * str_concat - concatenates two strings
 * @s1: input parameter1
 * @s2: input parameter2
 * Return: concatenated string
 */
char *str_concat(char *s1, char *s2)
{
	int i = 0, j = 0, size, k;
	char *array;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	for (; s1[i] != '\0'; i++)
		;
	for (; s2[j] != '\0'; j++)
		;
	size = i + j + 1;
	k = i;
	array = malloc(size);
	if (array == NULL)
		return (NULL);
	for (i = 0; i < size - 1; i++)
	{
		if (i < k)
			array[i] = s1[i];
		else
			array[i] = s2[i - k];
	}
	array[i] = '\0';
	return (array);
}

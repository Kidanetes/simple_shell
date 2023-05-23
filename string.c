#include "shell.h"
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
	for (i = 0; i < size; i++)
		array[i] = str[i];
	return (array);
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

	while (s1[i] == s2[i] && s1[i + 1] != '\0' && s2[i + 1] != '\0')
	{
		i++;
	}
	num = s1[i] - s2[i];

	return (num);
}

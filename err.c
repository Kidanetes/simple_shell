#include "main.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **argv, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @argv: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **argv, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(argv);
		break;
	case 1:
		error = error_1(argv);
		break;
	case 2:
		if (*(argv[0]) == 'e')
			error = error_2_exit(++argv);
		else if (argv[0][0] == ';' || argv[0][0] == '&' || argv[0][0] == '|')
			error = error_2_syntax(argv);
		else
			error = error_2_cd(argv);
		break;
	case 126:
		error = error_126(argv);
		break;
	case 127:
		error = error_127(argv);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}

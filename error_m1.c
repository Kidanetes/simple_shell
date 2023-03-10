#include "main.h"

char *error_env(char **argv);
char *error_1(char **argv);
char *error_2_exit(char **argv);
char *error_2_cd(char **argv);
char *error_2_syntax(char **argv);
/**
 * error_env - Creates an error message for shell_env errors.
 * @argv: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **argv)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	argv--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(argv[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, argv[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @argv: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **argv)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(argv[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, argv[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @argv: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **argv)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argv[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, argv[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @argv: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **argv)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (argv[0][0] == '-')
		argv[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_str) + _strlen(argv[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	if (argv[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, argv[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @argv: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **argv)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argv[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, argv[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}

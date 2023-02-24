#include "main.h"

int shell_alias(char **argv, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shell_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @argv: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_alias(char **argv, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *val;

	if (!argv[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; argv[i]; i++)
	{
		temp = aliases;
		val = _strchr(argv[i], '=');
		if (!val)
		{
			while (temp)
			{
				if (_strcmp(argv[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(argv + i, 1);
		}
		else
			set_alias(argv[i], val);
	}
	return (ret);
}
/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'val' or creates a new alias with 'name' and 'val'.
 * @var_name: Name of the alias.
 * @val: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *val)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')
			new_value[k++] = val[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->val);
			temp->val = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}
/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->val) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->val);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @argv: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **argv)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (_strcmp(argv[0], "alias") == 0)
		return (argv);
	for (i = 0; argv[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(argv[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->val) + 1));
				if (!new_value)
				{
					free_args(argv, argv);
					return (NULL);
				}
				_strcpy(new_value, temp->val);
				free(argv[i]);
				argv[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}
	return (argv);
}

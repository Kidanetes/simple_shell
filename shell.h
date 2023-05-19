#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int _strlen(char *s);
char **_strtok(char *str);
int number_of_words(char *str);

#endif

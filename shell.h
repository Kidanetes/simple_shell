#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <error.h>

extern char **environ;

char *get_path(void);
char **str_tok(char *str);
char *get_folder(char *input);
int _number_of_words(char *str);
int _strcmp(char *s1, char *s2);
char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
int _strlen(char *s);
char **_strtok(char *str);
int number_of_words(char *str);
void free_maloc(char **array);
void prompt(void);

#endif

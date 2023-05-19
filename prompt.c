#include "shell.h"
/**
 * main - reading the input from te user and displays it back
 *
 * Return: 0
 */
int main(void)
{
        char *string;
        size_t n = 100;

        string = malloc(sizeof(char) * n);
        printf("$ ");
        while (getline(&string, &n, stdin) != -1)
        {
                printf("%s", string);
                printf("$ ");
        }
        printf("\n");
        free(string);
        return (0);
}

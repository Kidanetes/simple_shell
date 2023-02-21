#include "main.h"


void execmd(char **argv){
    char *cmd = NULL, *actual_command = NULL;

    if (argv){
        /* get the command */
        cmd = argv[0];

        /* generate the path to this command before passing it to execve */
        actual_command = get_location(cmd);

        /* execute the actual command with execve */
        if (execve(actual_command, argv, environ) == -1){
            perror("Error:");
        }
    }
    
}

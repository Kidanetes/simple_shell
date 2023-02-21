#include "main.h"


int main(int ac, char **argv){
	char *prompt = "#cisfun$ ";
	char *command = NULL, *command_copy = NULL;
	size_t n = 0;
	ssize_t read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int status, i;

	/* declaring void variables */
	(void)ac;

	/* create an infinite loop */
	while(1){
		printf("%s", prompt);
		read = getline(&command, &n, stdin);

		/* check if the getline function failed or reached EOF*/
		if (read == -1){
			return (-1);
		}
		/* allocate space for a copy of the command */
		command_copy = malloc(sizeof(char) * read);
		if (command_copy== NULL){
			perror("tsh: memory allocation error");
			return (-1);
		}
		/* copy command to command_copy */
		strcpy(command_copy, command);

		/* split the string (command) into an array of words */
		/* calculate the total number of tokens */
		token = strtok(command, delim);

		while (token != NULL){
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* Allocate space to hold the array of strings */
		argv = malloc(sizeof(char *) * num_tokens);

		/* Store each token in the argv array */
		token = strtok(command_copy, delim);
		
		for (i = 0; token != NULL; i++){
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		if (strcmp(argv[0],"exit") == 0)
		{
			exit(0);
		}
		pid_t pid = fork ();
		
		if (pid < 0)
		{
			perror ("Error");
			return (1);
		}
		else if (pid == 0)
		{
			/* execute the command */
			 execmd(argv);	


		}
		else
		{
			wait (&status);
		}





		printf("%s\n", command);

		/* free up allocated memory */
	}
	free(command_copy);
	free(command);
	
	return (0);
}



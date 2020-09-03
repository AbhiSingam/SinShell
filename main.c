#include "headers.h"
// #include<string.h>

// Functions start
#include "prompt.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
// Functions end

int main()
{
	char *shell_dir = malloc(4096 * sizeof(char));
	getcwd(shell_dir, 4096);
    while (1)
    {
        prompt(shell_dir);

        char *input;
	    size_t insize = 4096;
	    size_t characters;

	    input = (char *)malloc(insize * sizeof(char));

	    if(input == NULL)
	    {
	        perror("Unable to take input");
	        exit(1);
	    }

	    characters = getline(&input,&insize,stdin);
	    int inlen = strlen(input);
    	input[inlen-1] = '\0';
    
        if(strcmp(input, "exit") == 0)
        {
        	exit(0);
        }

        else if(strcmp(input, "pwd") == 0)
        {
        	pwd(shell_dir);
        }

		else if(comp(input, "echo", 4) == 0)
		{
			echo(input);
		}

		else if(comp(input, "cd", 2)==0)
		{
			// printf("in-cd\n");
			cd(input);
		}

        else
        {
			// execvp(input);
        	printf("Command: \"%s\" not recognized\n", input);
        }
    }
}

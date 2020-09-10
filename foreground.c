#include "headers.h"
#include "foreground.h"

void foreground(char *in)
{
    char command[4096]="";
    char *arguments[1024];
    int switch_flag = 0, arg_count = 0;

    // printf("flag2\n");

    for (int e = 0; e < strlen(in); e++)
    {
        // printf("flag3\n");
        if (in[e] != ' ' && switch_flag < 1)
        {
            switch_flag++;
            int comm = 0, argu = 0;
            arguments[arg_count] = malloc(4096 * sizeof(char));
            for(int i=0;i<4096;i++)
            {
                arguments[arg_count][i]='\0';
            }
            while (in[e] != ' ')
            {
                command[comm] = in[e];
                arguments[arg_count][argu] = in[e];
                e++;
                argu++;
                comm++;
                if (e >= strlen(in))
                {
                    break;
                }
            }
            arg_count++;

            // printf("command: %s###\n", command);
        }
        else if (in[e] != ' ')
        {
            int argu = 0;
            arguments[arg_count] = malloc(4096 * sizeof(char));
            for (int it = 0; it < 4096; it++)
            {
                arguments[arg_count][it] = '\0';
            }
            while (in[e] != ' ')
            {
                // printf("flag4\n");
                arguments[arg_count][argu] = in[e];
                e++;
                argu++;
                if (e >= strlen(in))
                {
                    break;
                }
            }
            arg_count++;
            // printf("flag5\n");
        }
    }

    arguments[arg_count]=NULL;

    // for (int i = 0; i < arg_count; i++)
    // {
    //     printf("Arg%d: %s###\n", i, arguments[i]);
    // }

    pid_t pid;
    pid = fork();

    if(pid<0)
    {
        perror("fork");
        return;
    }
    else if(pid==0)
    {
        if(execvp(command, arguments)<0)
        {
            perror("execvp");
            _Exit(EXIT_FAILURE);
            // return;
        }
        _Exit(0);
        // return;
    }
    else
    {
        int status;
        waitpid(pid,&status,0);
        return;
        //wait for execvp (child process)
    }
    
}
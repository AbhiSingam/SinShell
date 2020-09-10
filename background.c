#include "headers.h"
#include "background.h"

void add_to_list(int pid, char *name)
{
    if(head->size==0)
    {
        head->pid=pid;
        int i=0;
        for(int j=0;j<4096;j++)
        {
            head->name[i]='\0';
        }
        while(name[i]!='\0')
        {
            head->name[i]=name[i];
            i++;
        }
        head->name[i]='\0';
        head->size++;
    }
    else
    {
        struct proc_info *curr = malloc(sizeof(struct proc_info));
        curr->next=head;
        curr->pid=pid;
        int i = 0;
        for (int j = 0; j < 4096; j++)
        {
            curr->name[i] = '\0';
        }
        while (name[i] != '\0')
        {
            curr->name[i] = name[i];
            i++;
        }
        curr->name[i] = '\0';
        curr->size=head->size+1;
        head->size=0;
        head=curr;
    }
    

    return;
}

char * name_from_pid(int pid)
{
    char *buf=malloc(4096 * sizeof(char));
    for(int j=0;j<4096;j++)
    {
        buf[j]='\0';
    }
    struct proc_info *curr = head;
    while(curr!=NULL)
    {
        if(curr->pid==pid)
        {
            int i=0;
            while(curr->name[i]!='\0')
            {
                buf[i]=curr->name[i];
                i++;
            }
            buf[i]='\0';
            break;
        }
        curr=curr->next;
    }
    return buf;
}

void if_signal(int signum)
{
    while(1)
    {
        int status;
        pid_t wpid, temp;
        int final_pid;

        temp = waitpid(-1, &status, WNOHANG); 
        if (temp > 0)
        {
            wpid=temp;
        }
        else
        {
            break;
        }
        char *final_name = name_from_pid(wpid);

        fprintf(stderr, "%s with pid %d exit with exit code: %d\n", final_name, wpid, WEXITSTATUS(status));
        
    }
}

void background(char *in)
{
    char command[4096] = "";
    char *arguments[1024];
    int switch_flag = 0, arg_count = 0;

    for (int e = 0; e < strlen(in); e++)
    {
        if (in[e] != ' ' && switch_flag < 1)
        {
            switch_flag++;
            int comm = 0, argu = 0;
            arguments[arg_count] = malloc(4096 * sizeof(char));
            for (int i = 0; i < 4096; i++)
            {
                arguments[arg_count][i] = '\0';
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
                arguments[arg_count][argu] = in[e];
                e++;
                argu++;
                if (e >= strlen(in))
                {
                    break;
                }
            }
            arg_count++;
        }
    }

    arguments[arg_count-1] = NULL;

    // for (int i = 0; i < arg_count; i++)
    // {
    //     printf("Arg%d: %s###\n", i, arguments[i]);
    // }

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        setpgid(pid,0);
        if (execvp(command, arguments) < 0)
        {
            perror("execvp");
            _exit(EXIT_FAILURE);
        }
        _exit(0);
    }
    else
    {
        setpgid(pid,0);
        add_to_list(pid,command);
        signal(SIGCHLD,if_signal);

        return;
    }
}
#include "headers.h"
#include "cd.h"

void cd(char *in)
{
    char *pwd = malloc(4096 * sizeof(char));
    getcwd(pwd,4096);

    char *out = malloc(strlen(in) * sizeof(char));
    char prev = ' ', curr;

    int j = 0;
    for (int i = 0; i < strlen(in); i++)
    {
        curr = in[i + 2];
        if (curr == ' ' && prev == ' ')
        {
            continue;
        }
        else
        {
            out[j] = curr;
            j++;
            prev = curr;
        }
    }

    char *rel_path = malloc((strlen(out)+strlen(pwd)+5) * sizeof(char));

    for(int i=0;i<strlen(pwd);i++)
    {
        rel_path[i]=pwd[i];
    }
    int pwdl = strlen(pwd);
    rel_path[pwdl]='/';
    for(int i=0;i<strlen(out);i++)
    {
        rel_path[i+pwdl+1]=out[i];
    }
    printf("rel_path: %s\n", rel_path);
    if(chdir(rel_path)==-1)
    {
        printf("failed\n");
        perror("cd:");
    }
}
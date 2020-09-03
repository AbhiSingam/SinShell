#include "headers.h"
#include "echo.h"

void echo(char *in)
{
    char *out = malloc(strlen(in) * sizeof(char));
    char prev = ' ', curr;

    int j=0;
    for(int i=0;i<strlen(in) - 4;i++)
    {
        curr = in[i+4];
        if(curr==' ' && prev==' ')
        {
            continue;
        }
        else
        {
            out[j]=curr;
            j++;
            prev=curr;
        }
    }
    printf("%s\n", out);
}
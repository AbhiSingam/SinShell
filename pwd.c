#include "headers.h"
#include "pwd.h"

int comp(char *a, char *b, int len)
{
	if(strlen(a)<len || strlen(b)<len)
	{
		return -1;
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			if(a[i]!=b[i])
			{
				return 1;
			}
		}
		return 0;
	}
	
}

void pwd(char *shell_dir)
{
	int SDlen = strlen(shell_dir);
	char *pwd = malloc(4096 * sizeof(char));
	getcwd(pwd, 4096);

	// if(comp(shell_dir, pwd, SDlen)==0 && strlen(shell_dir) < strlen(pwd))
	// {
	// 	char *rwd = malloc((strlen(pwd) - SDlen + 1) * sizeof(char));
	// 	rwd[0]='~';
	// 	rwd[1]='/';
	// 	for (int i = 2; i < strlen(pwd) - SDlen; i++)
	// 	{
	// 		rwd[i] = pwd[i+SDlen];
	// 	}
	// 	printf("%s\n", rwd);
	// }
	// else
	// {
		printf("%s\n", pwd);
	// }
}
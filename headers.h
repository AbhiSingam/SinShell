#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>    
#include <stdlib.h> 
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct proc_info
{
    struct proc_info *next;
    pid_t pid;
    char name[4096];
    int size;
};

struct proc_info *head;
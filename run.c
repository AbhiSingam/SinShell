#include "headers.h"
#include "run.h"

// Functions start
#include "prompt.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "foreground.h"
#include "background.h"
#include "history.h"
#include "redirection.h"
// Functions end

char * run(char *curr_com, char *shell_dir, char *prompt_dir)
{
    int else_flag = 0;

    if (comp(curr_com, "quit", 4) == 0)
    {
        if (strlen(curr_com) != 4)
        {
            if (curr_com[4] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                exit(0);
            }
        }

        else
        {
            exit(0);
        }
    }

    else if (comp(curr_com, "pwd", 3) == 0)
    {
        if (strlen(curr_com) != 3)
        {
            if (curr_com[3] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                pwd(shell_dir);
            }
        }

        else
        {
            pwd(shell_dir);
        }
    }

    else if (comp(curr_com, "echo", 4) == 0)
    {
        if (strlen(curr_com) != 4)
        {
            if (curr_com[4] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                echo(curr_com);
            }
        }

        else
        {
            echo(curr_com);
        }
    }

    else if (comp(curr_com, "cd", 2) == 0)
    {
        if (strlen(curr_com) != 2)
        {
            if (curr_com[2] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                cd(curr_com, shell_dir);
                prompt_dir = pwd2(shell_dir);
            }
        }

        else
        {
            cd(curr_com, shell_dir);
            prompt_dir = pwd2(shell_dir);
        }
    }

    else if (comp(curr_com, "ls", 2) == 0)
    {
        if (strlen(curr_com) != 2)
        {
            if (curr_com[2] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                ls(curr_com, shell_dir);
            }
        }

        else
        {
            ls(curr_com, shell_dir);
        }
    }

    else if (comp(curr_com, "pinfo", 5) == 0)
    {
        if (strlen(curr_com) != 5)
        {
            if (curr_com[5] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                pinfo(curr_com);
            }
        }

        else
        {
            pinfo(curr_com);
        }
    }

    else if (comp(curr_com, "history", 7) == 0)
    {
        if (strlen(curr_com) != 7)
        {
            if (curr_com[7] != ' ')
            {
                else_flag = 1;
            }
            else
            {
                history(curr_com, shell_dir);
            }
        }

        else
        {
            history(curr_com, shell_dir);
        }
    }

    else
    {
        if (curr_com[strlen(curr_com) - 1] != '&')
        {
            foreground(curr_com);
        }
        else
        {
            background(curr_com);
        }
    }

    if (else_flag)
    {
        if (curr_com[strlen(curr_com) - 1] != '&')
        {
            foreground(curr_com);
        }
        else
        {
            background(curr_com);
        }
    }

    return prompt_dir;
}
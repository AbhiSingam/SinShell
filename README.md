# SinShell
A custom shell I made using C

## How to run the shell:
- Run "make" in the SinShell directory.
- Then, run "./sin" to run the shell
- Type "exit" to exit the shell

## Implemented Commands:
- `pwd`
    * "pwd" will print the absolute path to the present working directory
    * pwd is implemented in "pwd.c' and "pwd.h"
- `echo [string]`
    * "echo [string]" will print the string in the terminal after removing extra white spaces (spaces-' ', and tabs-'\t')
    * echo is implemented in "echo.c" and "echo.h"
- `cd [directory path]`
    * "cd [directory path]" will change the present working directory of the terminal
    * "cd" or "cd ~" will change the present working directory to the home directory of the shell
    * cd is implemented in "cd.c" and "cd.h"
- `ls [flags] [directory path]`
    * "ls" lists all files present in the current working directory in alphabetical order
    * "ls [directory path]" lists all files present in the directory specified by [directory path] in alphabetical order
    * Possible flags: -l (displays extra information regarding files), -a (display all files, including hidden files), -al/-la (displays extra information regarding all files, including hidden files)
    * ls can also handle multiple [directory path]s, in which case it will list the files of all provided directories
    * the order in which the flags and [directory path]s are provided is inconsequential to the working of ls
    * ls is implemented in "ls.c" and "ls.h"
- `pinfo [pid]`
    * "pinfo" prints information regarding the process corresponding to the shell beingg executed
    * "pinfo [pid]" prints information regarding the process corresponding to the [pid] provided
    * pinfo makes use of the /proc/[pid]/stat and /proc/[pid]/exe files to obtain information regarding ongoing processes
    * To get process status and memory, it is assumed that they are the 3rd and 23rd elements in /proc/[pid]/stat, this is consistent with BASH shell
    * pinfo is implemented in "pinfo.c" and "pinfo.h"
- `history [number of commands]`
    * "history" lists the 10 most recently executed commands (incuding the history command)
    * "history [number of commands]` lists the [number of commands] most recently executed commands
    * if [number of commands] is entered as a value greater than 20, an error will be printed
    * if number of executed commands is less than requested number of commands, the maximum number of recorded commands will be printed
    * the executed commands are stored in "hist_info.txt", and if "hist_info.txt" does not exist then it will be created as a part of the command
    * history is implemented in "history.c" and "history.h"
- `exit`
    * "exit" exits the shell
    * exit is implemented in "main.c" directly

## Foreground and background processes:
- `foreground`
    * handles foreground processes other than the implemented commands using execvp
    * foreground is implemented in "foreground.c" and "foreground.h"
- `background`
    * handles background processes other than the implemented commands using execvp
    * printf info (name, pid, and exit status) of background processes when terminated
    * background is implemented in "background.c" and "background.h"

## Other implemented processes:
- `prompt`
    * prompt is run at the start of the shell loop and displays the username, system name and current directory.
    * prompt is implemented in "prompt.c" and "prompt.h"

## Other things to note:
- `';' separated commands`
    * SinShell is equipped to execute multiple ';' separated commands
- `Handling extra white space`
    * SinShell is equipped to handle extra spaces(' ') and tabs('\t') in commands
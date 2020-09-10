#include "headers.h"
// #include<string.h>

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
// Functions end

int main()
{
	head = malloc(sizeof(struct proc_info));
	head->next = NULL;
	head->size = 0;

	hist_head = malloc(sizeof(struct q));
	hist_head->after = 0;
	hist_head->next = NULL;
	hist_head->prev = NULL;

	char *shell_dir = malloc(4096 * sizeof(char));
	getcwd(shell_dir, 4096);

	char *prompt_dir = malloc(4096 * sizeof(char));
	prompt_dir = pwd2(shell_dir);

	init_hist_q(shell_dir);


	while (1)
	{
		// struct q *curr = hist_head;
		// while (curr != NULL)
		// {
		// 	printf("Name: %s, After: %d\n", curr->name, curr->after);
		// 	// printf("Name: %s\n", curr->name);
		// 	curr=curr->next;
		// }
		// printf("kkkkkk\n");
		prompt(prompt_dir);

		char *input;
		size_t insize = 4096;
		size_t characters;

		input = (char *)malloc(insize * sizeof(char));

		if (input == NULL)
		{
			perror("Unable to take input");
			exit(1);
		}

		characters = getline(&input, &insize, stdin);
		int inlen = strlen(input);
		input[inlen - 1] = '\0';

		char out[1024][4096];
		int input_count = 0;
		int j = 0;
		char prev = ' ';
		for (int i = 0; i < strlen(input); i++)
		{
			char curr = input[i];
			if (curr == ';')
			{
				if (out[0][0] != ' ')
				{
					out[input_count][j] = '\0';
					if (out[input_count][j - 1] == ' ')
					{
						out[input_count][j - 1] = '\0';
					}
					j = 0;
					prev = ' ';
					input_count++;
				}
			}
			else if ((curr == ' ' || curr == '\t' || curr == '\r') && (prev == ' ' || prev == '\t' || prev == '\r'))
			{
				continue;
			}
			else
			{
				out[input_count][j] = curr;
				j++;
				prev = curr;
			}
		}

		out[input_count][j] = '\0';
		if (out[input_count][j - 1] == ' ')
		{
			out[input_count][j - 1] = '\0';
		}

		// for(int i=0;i<=input_count;i++)
		// {
		// 	printf("input%d: %s###\n",i+1,out[i]);
		// }

		// printf("#out: %s#\n", out);

		char hist_text[4096]={'\0'};

		char prev2 = ' ', curr2;

		int jj = 0;
		for (int i = 0; i < strlen(input); i++)
		{
			curr2 = input[i];
			if ((curr2 == ' ' || curr2 == '\t' || curr2 == '\r') && (prev2 == ' ' || prev2 == '\t' || prev2 == '\r'))
			{
				continue;
			}
			else
			{
				hist_text[jj] = curr2;
				jj++;
				prev2 = curr2;
			}
		}
		hist_text[j] = '\0';

		add_comm(hist_text, shell_dir);
		
		for (int i = 0; i <= input_count; i++)
		{
			int else_flag = 0;

			if (out[i][0] == '\0' || out[i][0] == ' ' || out[i][0] == '\t' || out[i][0] == '\r')
			{
				continue;
			}

			// printf("now add_com\n");


			// printf("done add_comm\n");

			// printf("out%d: %s###\n", i, out[i]);
			if (comp(out[i], "exit", 4) == 0)
			{
				if (strlen(out[i]) != 4)
				{
					if (out[i][4] != ' ')
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

			else if (comp(out[i], "pwd", 3) == 0)
			{
				if (strlen(out[i]) != 3)
				{
					if (out[i][3] != ' ')
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

			else if (comp(out[i], "echo", 4) == 0)
			{
				if (strlen(out[i]) != 4)
				{
					if (out[i][4] != ' ')
					{
						else_flag = 1;
					}
					else
					{
						echo(out[i]);
					}
				}

				else
				{
					echo(out[i]);
				}
			}

			else if (comp(out[i], "cd", 2) == 0)
			{
				if (strlen(out[i]) != 2)
				{
					if (out[i][2] != ' ')
					{
						else_flag = 1;
					}
					else
					{
						cd(out[i], shell_dir);
						prompt_dir = pwd2(shell_dir);
					}
				}

				else
				{
					cd(out[i], shell_dir);
					prompt_dir = pwd2(shell_dir);
				}
			}

			else if (comp(out[i], "ls", 2) == 0)
			{
				if (strlen(out[i]) != 2)
				{
					if (out[i][2] != ' ')
					{
						else_flag = 1;
					}
					else
					{
						ls(out[i], shell_dir);
					}
				}

				else
				{
					ls(out[i], shell_dir);
				}
			}

			else if (comp(out[i], "pinfo", 5) == 0)
			{
				if (strlen(out[i]) != 5)
				{
					if (out[i][5] != ' ')
					{
						else_flag = 1;
					}
					else
					{
						pinfo(out[i]);
					}
				}

				else
				{
					pinfo(out[i]);
				}
			}

			else if (comp(out[i], "history", 7) == 0)
			{
				if (strlen(out[i]) != 7)
				{
					if (out[i][7] != ' ')
					{
						else_flag = 1;
					}
					else
					{
						history(out[i], shell_dir);
					}
				}

				else
				{
					history(out[i], shell_dir);
				}
			}

			else
			{
				if (out[i][strlen(out[i]) - 1] != '&')
				{
					foreground(out[i]);
				}
				else
				{
					background(out[i]);
				}
			}

			if (else_flag)
			{
				if (out[i][strlen(out[i]) - 1] != '&')
				{
					foreground(out[i]);
				}
				else
				{
					background(out[i]);
				}
			}
		}
	}
}

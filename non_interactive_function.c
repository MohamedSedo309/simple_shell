#include "shell.h"

/**
 *run_shell_interactively - run shell interactively
 *Return: void
 */
void run_shell_interactively(void)
{
	char **curcmd = NULL;
	int i, cmdtyp = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&input_line, &n, stdin) != -1)
		{
			remove_newline_character(input_line);
			remove_comments(input_line);
			input_commands = tokenizer(input_line, ";");
			for (i = 0; input_commands[i] != NULL; i++)
			{
				curcmd = tokenizer(input_commands[i], " ");
				if (curcmd[0] == NULL)
				{
					free(curcmd);
					break;
				}
				cmdtyp = parse_input_command(curcmd[0]);
				initialize_shell(curcmd, cmdtyp);
				free(curcmd);
			}
			free(input_commands);
		}
		free(input_line);
		exit(status);
	}
}

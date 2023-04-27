#include "shell.h"
char **input_commands = NULL;
char *input_line = NULL;
char *shell_name = NULL;
int status = 0;

int main(int argc __attribute__((unused)), char **arnn)
{
	char **current_command = NULL;
	int i, type_command = 0;
	size_t n = 0;

	signal(SIGINT, ctrl_c_signal_handler);
	shell_name = arnn[0];
	while (1)
	{
		run_shell_interactively();
		print_message(" ($) ", STDOUT_FILENO);
		if (getline(&input_line, &n, stdin) == -1)
		{
			free(input_line);
			exit(status);
		}
			remove_newline_character(input_line);
			remove_comments(input_line);
			input_commands = tokenize_string(input_line, ";");

		for (i = 0; input_commands[i] != NULL; i++)
		{
			current_command = tokenize_string(input_commands[i], " ");
			if (current_command[0] == NULL)
			{
				free(current_command);
				break;
			}
			type_command = parse_input_command(current_command[0]);
			initialize_shell(current_command, type_command);
			free(current_command);
		}
		free(input_commands);
	}
	free(input_line);

	return (status);
}

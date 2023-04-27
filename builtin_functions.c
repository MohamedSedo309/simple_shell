#include "shell.h"

/**
 *show_environment_variables- prints current environnement
 *@tok_cmd: the entered command
 *Return: void
 */
void show_environment_variables(char **tok_cmd __attribute__((unused)))
{
	int i;

	for (i = 0; environment[i] != NULL; i++)
	{
		print_message(environment[i], STDOUT_FILENO);
		print_message("\n", STDOUT_FILENO);
	}
}

/**
 *exit_shell - exits the shell
 *@tok_cmd: the entered command
 *Return: void
 */
void exit_shell(char **tok_cmd)
{
	int nt = 0, arg;

	for (; tok_cmd[nt] != NULL; nt++)
		;
	if (nt == 1)
	{
		free(tok_cmd);
		free(input_line);
		free(input_commands);
		exit(status);
	}
	else if (nt == 2)
	{
		arg = _atoi(tok_cmd[1]);
		if (arg == -1)
		{
			print_message(shell_name, STDERR_FILENO);
			print_message(": 1: exit: Illegal number: ", STDERR_FILENO);
			print_message(tok_cmd[1], STDERR_FILENO);
			print_message("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(input_line);
			free(tok_cmd);
			free(input_commands);
			exit(arg);
		}
	}
	else
		print_message("exit, only one arg\n", STDERR_FILENO);
}

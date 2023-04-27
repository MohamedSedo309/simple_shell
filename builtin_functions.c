#include "shell.h"

/**
 *env - prints current environnement
 *@tok_cmd: the entered command
 *Return: void
 */
void env(char **tok_cmd __attribute__((unused)))
{
	int i;

	for (i = 0; environment[i] != NULL; i++)
	{
		print(environment[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - exits the shell
 *@tok_cmd: the entered command
 * Return: void
 */
void quit(char **tok_cmd)
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
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tok_cmd[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
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
		print("exit, only one arg\n", STDERR_FILENO);
}

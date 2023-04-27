#include "shell.h"

/**
 *Auth: Saif Abd Elfattah
 *Mohamed sedo
 *Description:
 *the extended functions for main.c
 */


/**
 *parse_input_command - determines the type of the command
 *@cmmd: command to be parsed
 *Return: constant representing the type of the command
 *Description -
 *EXTERNAL_COMMAND (1) represents commands like /bin/ls
 *INTERNAL_COMMAND (2) represents commands like exit, env
 *PATH_COMMAND (3) represents commands found in the PATH like ls
 *INVALID_COMMAND (-1) represents invalid commands
 */
int parse_input_command(char *cmmd)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; cmmd[i] != '\0'; i++)
	{
		if (cmmd[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(cmmd, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	path = check_path(cmmd);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 *execute_command - executes a command based on type
 *@token_cmmd: tokenized form of the command
 *@cmd_type: command type
 *Return: void
 */
void execute_input_command(char **token_cmmd, int cmd_type)
{
	void (*func)(char **command);

	if (cmd_type == EXTERNAL_COMMAND)
	{
		if (execve(token_cmmd[0], token_cmmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmd_type == PATH_COMMAND)
	{
		if (execve(check_path(token_cmmd[0]), token_cmmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmd_type == INTERNAL_COMMAND)
	{
		func = get_func(token_cmmd[0]);
		func(token_cmmd);
	}
	if (cmd_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(token_cmmd[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 *find_command_in_path - checks if a command is found
 *@command: command to be used
 *Return: path of command or NULL
 */
char *find_command_in_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 *get_command_function-get the right function based
 *on the given command
 *@command:string to check against the mapping
 *Return: pointer to function or Null
 */
void (*get_command_function(char *command))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 *get_environment_variable-gets the value of an environment variable
 *@cu_env: current env
 *Return: string
 */
char *get_environment_variable(char *cu_env)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = cu_env;
		     *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}

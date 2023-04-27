#include "shell.h"

/**
 *initialize_shell - starts executing everything
 *@curcmd: try to check current token
 *@cmdtyp: parse token
 *Return: void function
 */
void initialize_shell(char **curcmd, int cmdtyp)
{
	pid_t mypid;

	if (cmdtyp == EXTERNAL_COMMAND || cmdtyp == PATH_COMMAND)
	{
		mypid = fork();
		if (mypid == 0)
			execute_command(curcmd, cmdtyp);
		else
		{
			waitpid(mypid, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(curcmd, cmdtyp);
}
